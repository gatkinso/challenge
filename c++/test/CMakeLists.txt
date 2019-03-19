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

