cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings VERSION 1.0.0)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    if(WIN32)
        string(REPLACE "\\" "/" USER_HOME "$ENV{USERPROFILE}")
        set(CMAKE_INSTALL_PREFIX "${USER_HOME}/.cmake/packages" CACHE PATH "..." FORCE)
        set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}" CACHE PATH "..." FORCE)
    elseif(UNIX)
        set(USER_HOME "$ENV{HOME}" CACHE PATH "..." FORCE)
        set(CMAKE_INSTALL_PREFIX "${USER_HOME}/.cmake/packages" CACHE PATH "..." FORCE)
        set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}" CACHE PATH "..." FORCE)
    endif()
endif()

set(CMAKE_CXX_STANDARD 20)

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

install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME} DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/lib")
install(EXPORT ${LIBRARY_NAME} FILE "${LIBRARY_NAME}-config.cmake" DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/include/exqudens")
