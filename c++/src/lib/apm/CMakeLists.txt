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

set(TARGETNAME apm)
set(${TARGETNAME}_INC_DIR ${PROJECT_SOURCE_DIR}/c++/include/${TARGETNAME})

include_directories(
                   ${${TARGETNAME}_INC_DIR}
)

set(LINK_LIBS )
set(${TARGETNAME}_SOURCES ${TARGETNAME}.cpp)
set(BUILD_SHARED_LIBS FALSE)

add_library(${TARGETNAME} STATIC ${${TARGETNAME}_SOURCES})

target_link_libraries(${TARGETNAME} ${LINK_LIBS})

if(GENERATE_COV)
    add_custom_command(TARGET ${TARGETNAME} POST_BUILD
        COMMAND echo "=================== GCOV LIB ===================="
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
        COMMAND gcov ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.gcno
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcno ${CMAKE_BINARY_DIR}/coverage
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcda ${CMAKE_BINARY_DIR}/coverage          
        COMMAND lcov --capture --initial --directory ${CMAKE_BINARY_DIR}/coverage --output-file ${CMAKE_BINARY_DIR}/coverage/lcovoutput-libapm.info
    )
endif(GENERATE_COV)
