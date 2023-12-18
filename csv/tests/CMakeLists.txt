cmake_minimum_required(VERSION 3.26)
project(csv_tests)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES csv_read_tests.cpp)

enable_testing()
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}
	GTest::gtest_main
	csv
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})