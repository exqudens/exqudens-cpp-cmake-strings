cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/main/cpp)

SET(
        EXQUDENS_STRINGS_HPP_FILES
        src/main/cpp/exqudens/strings.hpp
)

SET(
        EXQUDENS_STRINGS_CPP_FILES
        src/main/cpp/exqudens/strings.cpp
)

add_library(
        exqudens_strings
        STATIC
        ${EXQUDENS_STRINGS_CPP_FILES}
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

set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS exqudens_strings DESTINATION lib)
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION include)
