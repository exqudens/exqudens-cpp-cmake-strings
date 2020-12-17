cmake_minimum_required(VERSION 3.17)

set(PROJECT_GROUP "exqudens")

project("${PROJECT_GROUP}-cpp-cmake-strings" VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# set '${USER_HOME}'
if(WIN32)
    string(REPLACE "\\" "/" USER_HOME "$ENV{USERPROFILE}")
elseif(UNIX)
    set(USER_HOME "$ENV{HOME}")
else()
    message(FATAL_ERROR "Can't set USER_HOME")
endif()

# set install path to '${USER_HOME}/.cmake/packages'
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${USER_HOME}/.cmake/packages" CACHE PATH "..." FORCE)
    set(CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}" CACHE PATH "..." FORCE)
endif()

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/exqudens/strings.hpp>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/exqudens/strings.hpp>
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp/exqudens/strings.cpp>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/lib/exqudens/strings.cpp>
)
target_include_directories(${PROJECT_NAME}
    INTERFACE
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include/exqudens>
    PRIVATE
        src/main/cpp
)

enable_testing()

add_executable(${PROJECT_NAME}_tests_1 src/test/cpp/tests_1.cpp)
target_link_libraries(${PROJECT_NAME}_tests_1
    INTERFACE
        src/main/cpp/exqudens/strings.hpp
    PUBLIC
        ${PROJECT_NAME}
)
target_include_directories(${PROJECT_NAME}_tests_1
    PRIVATE
        src/main/cpp
)

add_test(${PROJECT_NAME}_tests_1_test_1 ${PROJECT_NAME}_tests_1 test_1)

add_custom_command(
        TARGET ${PROJECT_NAME}_tests_1
        POST_BUILD
        COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --output-on-failure
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/lib/cmake
)

set(version 3.4.1)

set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION ${version})
set_property(TARGET ${PROJECT_NAME} PROPERTY SOVERSION 3)
set_property(TARGET ${PROJECT_NAME} PROPERTY INTERFACE_${PROJECT_NAME}_MAJOR_VERSION 3)
set_property(TARGET ${PROJECT_NAME} APPEND PROPERTY COMPATIBLE_INTERFACE_STRING ${PROJECT_NAME}_MAJOR_VERSION)

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        VERSION "${version}"
        COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION
        ${PROJECT_NAME}-${PROJECT_VERSION}/cmake
)

install(
    TARGETS ${PROJECT_NAME}
    EXPORT ${PROJECT_NAME}Targets
    LIBRARY DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/lib
    ARCHIVE DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/lib
    RUNTIME DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/bin
    INCLUDES DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/include
)
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/include/exqudens)
install(
    EXPORT ${PROJECT_NAME}Targets
    FILE ${PROJECT_NAME}Targets.cmake
    NAMESPACE ${PROJECT_NAME}::
    DESTINATION ${PROJECT_NAME}-${PROJECT_VERSION}/cmake
)

#configure_file(version.cmake.in "${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake" @ONLY)

#install(TARGETS ${LIBRARY_NAME} EXPORT ${LIBRARY_NAME} DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/lib")
#install(EXPORT ${LIBRARY_NAME} FILE "${LIBRARY_NAME}-config.cmake" DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${LIBRARY_NAME}-config-version.cmake DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}")
#install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION "${LIBRARY_NAME}-${PROJECT_VERSION}/include/exqudens")
