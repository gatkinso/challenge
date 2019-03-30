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

include_directories()
add_executable(${TARGETNAME} 
                main.cpp
                request_unit_test.cpp
                response_unit_test.cpp
)

target_link_libraries(${TARGETNAME} GTest::GTest GTest::Main ${PLATFORM_LINK_LIBS})

gtest_discover_tests(${TARGETNAME} TEST_PREFIX challenge_generated_tests:)

add_dependencies(${TARGETNAME} agent)

add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov ${CMAKE_CURRENT_BINARY_DIR}/main.gnco
    COMMAND lcov --capture --directory ${CMAKE_CURRENT_BINARY_DIR} --output-file lcovoutput.info
    COMMAND genhtml lcovoutput.info --output-directory ${CMAKE_BINARY_DIR}/code_coverage
)

add_dependencies(gcov ${TARGETNAME})

