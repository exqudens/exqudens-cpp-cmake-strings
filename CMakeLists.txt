cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/main/cpp)

add_library(
        exqudens_strings
        src/main/cpp/exqudens/strings.hpp
        src/main/cpp/exqudens/strings.cpp
)

enable_testing()

add_executable(tests_1 src/test/cpp/tests_1.cpp)
target_link_libraries(
        tests_1
        PUBLIC
        exqudens_strings
)

add_test(tests_1_test_1 tests_1 test_1)

add_custom_command(
        TARGET tests_1
        POST_BUILD
        COMMAND ctest -C $<CONFIGURATION> --output-on-failure
)
