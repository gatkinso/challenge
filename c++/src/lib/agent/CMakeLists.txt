set(TARGETNAME agent)
set(${TARGETNAME}_INC_DIR ${PROJECT_SOURCE_DIR}/include/${TARGETNAME})

find_package(Python3 COMPONENTS Interpreter Development)
 
include_directories(
                   ${${TARGETNAME}_INC_DIR}
                   ${Python3_INCLUDE_DIRS}
)

set(LINK_LIBS ${Python3_LIBRARIES})
set(${TARGETNAME}_SOURCES ${TARGETNAME}.cpp)
set(BUILD_SHARED_LIBS TRUE)

add_library(${TARGETNAME} SHARED ${${TARGETNAME}_SOURCES})

target_link_libraries(${TARGETNAME} ${LINK_LIBS})

