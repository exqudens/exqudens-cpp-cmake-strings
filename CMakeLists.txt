cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/main/cpp)

add_library(
        exqudens_strings
        STATIC
        src/main/cpp/exqudens/strings.cpp
)

enable_testing()

add_executable(${CMAKE_PROJECT_NAME}_tests_1 src/test/cpp/tests_1.cpp)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}_tests_1
        PUBLIC
        exqudens_strings
)

add_test(${CMAKE_PROJECT_NAME}_tests_1_test_1 ${CMAKE_PROJECT_NAME}_tests_1 test_1)

add_custom_command(
        TARGET ${CMAKE_PROJECT_NAME}_tests_1
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS exqudens_strings DESTINATION lib)
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION include)
