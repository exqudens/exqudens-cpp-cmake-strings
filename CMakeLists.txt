cmake_minimum_required(VERSION 3.17)

set(PROJECT_GROUP "exqudens")

project("${PROJECT_GROUP}-cpp-cmake-strings" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

include(extension.cmake)

directories(src/main/cpp)

add_library(
        exqudens-strings
        STATIC
        src/main/cpp/exqudens/strings.cpp
)

library(exqudens-strings)

enable_testing()

add_executable(${PROJECT_NAME}_tests_1 src/test/cpp/tests_1.cpp)
target_link_libraries(
        ${PROJECT_NAME}_tests_1
        PUBLIC
        ${LIBRARIES}
)

add_test(${PROJECT_NAME}_tests_1_test_1 ${PROJECT_NAME}_tests_1 test_1)

add_custom_command(
        TARGET ${PROJECT_NAME}_tests_1
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
)

#configure_file(version.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake" @ONLY)

#install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME} DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/lib")
#install(EXPORT ${LIBRARY_NAME} FILE "${LIBRARY_NAME}-config.cmake" DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
#install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/include/exqudens")
