cmake_minimum_required(VERSION 3.0.0)

set(PROJECT ghVector)

project(${PROJECT} VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

enable_testing()
include(GoogleTest)
add_subdirectory(tests)

add_library(${PROJECT} src/ghVector.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

