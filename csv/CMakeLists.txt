cmake_minimum_required(VERSION 3.26)
project(csv)

set(SOURCE_FILES csv.cpp csv.h)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC .)

add_subdirectory(tests)
