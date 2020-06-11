cmake_minimum_required(VERSION 3.12)
project(AnalizadorLexico VERSION 1.0.1)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/build/")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_executable(analizadorLexico ${SOURCES})