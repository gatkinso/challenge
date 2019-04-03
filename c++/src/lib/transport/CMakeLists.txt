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

set(TARGETNAME transport)

set(PROTO_FILES
    transport
)

set(PROTO_CPP_DIR "${PROJECT_BINARY_DIR}/proto/cpp")
set(PROTO_PYTHON_DIR "${PROJECT_BINARY_DIR}/proto/python")

if(UNIX)
    file(MAKE_DIRECTORY ${PROTO_CPP_DIR}) 
    file(MAKE_DIRECTORY ${PROTO_PYTHON_DIR})
endif(UNIX)

foreach(PROTO ${PROTO_FILES})
    #cpp
    add_custom_command(
        OUTPUT  ${PROTO_CPP_DIR}/${PROTO}.pb.h
                ${PROTO_CPP_DIR}/${PROTO}.pb.cc
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO}.proto
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS    ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO}.proto
                --cpp_out=${PROTO_CPP_DIR}
                --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
    )
    set(PROTOCPP_RESULTS ${PROTOCPP_RESULTS}
        ${PROTO_CPP_DIR}/${PROTO}.pb.cc
        ${PROTO_CPP_DIR}/${PROTO}.pb.h
    )
    #python
    add_custom_command(
        OUTPUT  ${PROTO_PYTHON_DIR}/${PROTO}.pb.py
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO}.proto
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE}
        ARGS    ${CMAKE_CURRENT_SOURCE_DIR}/${PROTO}.proto
                --python_out=${PROTO_PYTHON_DIR}
                --proto_path=${CMAKE_CURRENT_SOURCE_DIR}
    )
    set(PROTOPY_RESULTS ${PROTOPY_RESULTS}
        ${PROTO_PYTHON_DIR}/${PROTO}.pb.py
    )
endforeach(PROTO)

set_property(SOURCE ${PROTOCPP_RESULTS} APPEND PROPERTY OBJECT_DEPENDS ${PROTOPY_RESULTS})

add_library(${TARGETNAME} STATIC ${PROTOCPP_RESULTS})

if(MSVC)
    target_compile_options(${TARGETNAME} PRIVATE "/wd4800")
endif(MSVC)

target_link_libraries(${TARGETNAME} ${PROTOBUF_LIBRARIES})
