# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set(TARGETNAME challenge_tests)

include_directories(
                ${PROJECT_SOURCE_DIR}/c++/include/apm
                ${PROJECT_SOURCE_DIR}/c++/include/hasher
                ${PROJECT_BINARY_DIR}/proto/cpp
)

add_executable(${TARGETNAME} 
                main.cpp
                apm_unit_test.cpp
                hasher_unit_test.cpp
                request_unit_test.cpp
                response_unit_test.cpp
)

target_link_libraries(${TARGETNAME} GTest::GTest GTest::Main ${PLATFORM_LINK_LIBS} apm agent hasher transport)

gtest_discover_tests(${TARGETNAME} TEST_PREFIX challenge_generated_tests:)

add_dependencies(${TARGETNAME} agent apm hasher transport)

if(GENERATE_COV)
    add_custom_target(gcov
        COMMAND ${CMAKE_MAKE_PROGRAM} test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )  

    set(INFOFILES 
        -a ${CMAKE_BINARY_DIR}/coverage/lcovoutput.info 
        -a ${CMAKE_BINARY_DIR}/coverage/lcovoutput-libagent.info 
        -a ${CMAKE_BINARY_DIR}/coverage/lcovoutput-libapm.info
        -a ${CMAKE_BINARY_DIR}/coverage/lcovoutput-libhasher.info
    )
    add_custom_command(TARGET gcov
        COMMAND echo "=================== GCOV TEST ===================="
        COMMAND gcov ${CMAKE_CURRENT_BINARY_DIR}/*.gnco
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcno ${CMAKE_BINARY_DIR}/coverage
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcda ${CMAKE_BINARY_DIR}/coverage
        COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR}/coverage --output-file ${CMAKE_BINARY_DIR}/coverage/lcovoutput.info
        COMMAND lcov ${INFOFILES}  -o ${CMAKE_BINARY_DIR}/challenge.info
        COMMAND genhtml ${CMAKE_BINARY_DIR}/challenge.info --output-directory ${CMAKE_BINARY_DIR}/code_coverage
    )

    add_dependencies(gcov ${TARGETNAME})
endif(GENERATE_COV)

