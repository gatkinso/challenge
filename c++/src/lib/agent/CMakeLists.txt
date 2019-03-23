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
set(${TARGETNAME}_INC_DIR ${PROJECT_SOURCE_DIR}/include/${TARGETNAME})

set(Python_ADDITIONAL_VERSIONS 3.6)
find_package(Python3 COMPONENTS Development)
 
include_directories(
                   ${${TARGETNAME}_INC_DIR}
                   ${Python3_INCLUDE_DIRS}
)

set(LINK_LIBS ${Python3_LIBRARIES})
set(${TARGETNAME}_SOURCES ${TARGETNAME}.cpp)
set(BUILD_SHARED_LIBS TRUE)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_SOURCES})

target_link_libraries(${TARGETNAME} ${LINK_LIBS})

