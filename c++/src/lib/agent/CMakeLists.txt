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

set(TARGETNAME agent)
set(${TARGETNAME}_INC_DIR ${PROJECT_SOURCE_DIR}/c++/include/${TARGETNAME})

set(Python_ADDITIONAL_VERSIONS 3.6)
find_package(Python3 COMPONENTS Development)
 
include_directories(
                   ${${TARGETNAME}_INC_DIR}
                   ${PROJECT_SOURCE_DIR}/c++/include/apm
                   ${PROJECT_BINARY_DIR}/proto/cpp
                   ${Python3_INCLUDE_DIRS}
)

set(LINK_LIBS ${Python3_LIBRARIES} apm)
set(${TARGETNAME}_SOURCES ${TARGETNAME}.cpp)
set(BUILD_SHARED_LIBS TRUE)

add_compile_options(-fPIC)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_SOURCES})

target_link_libraries(${TARGETNAME} ${LINK_LIBS})

set(PYTHON_FILES
    ${CMAKE_SOURCE_DIR}/python/app.py
    ${CMAKE_SOURCE_DIR}/python/unit_test.py
    ${CMAKE_SOURCE_DIR}/python/flask-exagent/flask_exagent.py
)

add_custom_command(TARGET ${TARGETNAME} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy 
     "$<TARGET_FILE:${TARGETNAME}>"
     "${CMAKE_BINARY_DIR}/staging/$<TARGET_FILE_NAME:${TARGETNAME}>"
  COMMENT "Copying to output directory"
)

add_custom_command(TARGET ${TARGETNAME} POST_BUILD 
      COMMAND "${CMAKE_COMMAND}" -E copy ${PYTHON_FILES} ${CMAKE_BINARY_DIR}/staging/
      COMMENT "Copying Python to output directory"
)

if(GENERATE_COV)
    add_custom_command(TARGET ${TARGETNAME} POST_BUILD
        COMMAND echo "=================== GCOV LIB ===================="
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/coverage
        COMMAND gcov ${CMAKE_CURRENT_BINARY_DIR}/${TARGETNAME}.gcno
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcno ${CMAKE_BINARY_DIR}/coverage
        #COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${TARGETNAME}.dir/*.gcda ${CMAKE_BINARY_DIR}/coverage          
        COMMAND lcov --capture --initial --directory ${CMAKE_BINARY_DIR}/coverage --output-file ${CMAKE_BINARY_DIR}/coverage/lcovoutput-lib${TARGETNAME}.info
    )
endif(GENERATE_COV)
