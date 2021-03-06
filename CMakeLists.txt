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
    
cmake_minimum_required(VERSION 3.8)

project(challenge)

include (CTest)
enable_testing()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/staging)

if(GENERATE_COV)
    set(CMAKE_CXX_FLAGS "-g -O0 -Wall --coverage")
    set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)  
endif(GENERATE_COV)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})

include(FindPythonInterp)
add_test(NAME PythonTest 
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_BINARY_DIR}/staging/unit_test.py 
    WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}
)

add_subdirectory(c++)


