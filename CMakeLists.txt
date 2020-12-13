cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INSTALL_PREFIX "$ENV{HOME}/.cmake/packages")
set(CMAKE_PREFIX_PATH "$ENV{HOME}/.cmake/packages")

set(LIBRARY_NAME "exqudens_strings")

include_directories(src/main/cpp)

add_library(
        ${LIBRARY_NAME}
        STATIC
        src/main/cpp/exqudens/strings.cpp
)

enable_testing()

add_executable(${PROJECT_NAME}_tests_1 src/test/cpp/tests_1.cpp)
target_link_libraries(
        ${PROJECT_NAME}_tests_1
        PUBLIC
        exqudens_strings
)

add_test(${PROJECT_NAME}_tests_1_test_1 ${PROJECT_NAME}_tests_1 test_1)

add_custom_command(
        TARGET ${PROJECT_NAME}_tests_1
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
)

configure_file(version.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake" @ONLY)

install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME} DESTINATION "lib/${LIBRARY_NAME}-${PROJECT_VERSION}")
install(EXPORT ${LIBRARY_NAME} FILE "${LIBRARY_NAME}-config.cmake" DESTINATION "lib/${LIBRARY_NAME}-${PROJECT_VERSION}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake DESTINATION "lib/${LIBRARY_NAME}-${PROJECT_VERSION}")
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION "include/${LIBRARY_NAME}-${PROJECT_VERSION}/exqudens")
