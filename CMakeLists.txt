cmake_minimum_required(VERSION 3.8)

project(compression)

set(CXX_STANDARD 20)

file(GLOB SRC_LIST
"${PROJECT_SOURCE_DIR}/*.h"
"${PROJECT_SOURCE_DIR}/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_LIST})