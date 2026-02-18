cmake_minimum_required(VERSION 4.2.3)
project(cpp-template LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(src)

file(GLOB_RECURSE ALL_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.hpp
    ${CMAKE_SOURCE_DIR}/tests/*.cpp
    ${CMAKE_SOURCE_DIR}/tests/*.hpp
)

find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
    add_custom_target(format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCES}
        COMMENT "Formatting sources"
    )
    add_custom_target(format-check
        COMMAND ${CLANG_FORMAT} --dry-run --Werror ${ALL_SOURCES}
        COMMENT "Checking formatting"
    )
endif()

find_program(CLANG_TIDY clang-tidy)
if(CLANG_TIDY)
    set(RUN_CLANG_TIDY_SCRIPT ${CMAKE_BINARY_DIR}/run_clang_tidy.sh)
    configure_file(${CMAKE_SOURCE_DIR}/cmake/run_clang_tidy.sh.in ${RUN_CLANG_TIDY_SCRIPT} @ONLY)

    add_custom_target(lint
        COMMAND bash ${RUN_CLANG_TIDY_SCRIPT} ${ALL_SOURCES}
        COMMENT "Running clang-tidy"
    )
    add_custom_target(lint-fix
        COMMAND bash ${RUN_CLANG_TIDY_SCRIPT} --fix ${ALL_SOURCES}
        COMMENT "Running clang-tidy with fixes"
    )
endif()

option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/releases/download/v1.17.0/googletest-1.17.0.tar.gz
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()
    add_subdirectory(tests)
endif()
