cmake_minimum_required(VERSION 3.8)

project(compression)

set(CXX_STANDARD 20)

file(GLOB SRC_LIST
"${PROJECT_SOURCE_DIR}/*.h"
"${PROJECT_SOURCE_DIR}/*.cpp"
"task_completion_percentage.cpp"
"task_completion_percentage.h"
)

add_executable(${PROJECT_NAME} ${SRC_LIST})

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    option(BUILD_TESTS "build tests (or no)" ON)

    if (BUILD_TESTS)
                add_library(example_google_tests ${SRC_LIST})
                enable_testing()
                add_subdirectory(tests)
        endif()
endif()