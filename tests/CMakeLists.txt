include(GoogleTest)

add_library(subprocess STATIC helpers/subprocess.cpp)
target_include_directories(subprocess PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(subprocess PUBLIC BINARY_DIR="${CMAKE_BINARY_DIR}")

file(GLOB_RECURSE TEST_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*/test_*.cpp")

foreach(TEST_FILE ${TEST_FILES})
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FILE})
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest_main subprocess)
    target_include_directories(${TEST_NAME} PRIVATE
        ${CMAKE_SOURCE_DIR}/src
    )

    gtest_discover_tests(${TEST_NAME})
endforeach()
