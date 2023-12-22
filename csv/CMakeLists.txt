cmake_minimum_required(VERSION 3.26)
project(csv)

set(SOURCE_FILES csv.cpp csv.h document_reader.cpp document_reader.h parser.inl)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC .)

add_subdirectory(tests)
