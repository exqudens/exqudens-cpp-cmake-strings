cmake_minimum_required(VERSION 3.17)
project(exqudens_cpp_cmake_strings VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)

# include home configuration from user_home/.cmake/CMakeLists.txt
if(DEFINED ENV{HOME})
    set(HOME "$ENV{HOME}")
    if (EXISTS "${HOME}/.cmake/CMakeLists.txt")
        include("${HOME}/.cmake/CMakeLists.txt")
    endif()
elseif(DEFINED ENV{HOMEDRIVE} AND DEFINED ENV{HOMEPATH})
    STRING(REPLACE "\\" "/" HOME "$ENV{HOMEDRIVE}$ENV{HOMEPATH}")
    if (EXISTS "${HOME}/.cmake/CMakeLists.txt")
        include("${HOME}/.cmake/CMakeLists.txt")
    endif()
endif()

include_directories(src/main/cpp)

add_library(
        exqudens_strings
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

install(TARGETS exqudens_strings EXPORT exqudens_strings DESTINATION "${PROJECT_NAME}-${PROJECT_VERSION}/lib")
install(EXPORT exqudens_strings FILE exqudens_strings-config.cmake DESTINATION "${PROJECT_NAME}-${PROJECT_VERSION}")
install(FILES src/main/cpp/exqudens/strings.hpp DESTINATION "${PROJECT_NAME}-${PROJECT_VERSION}/include/exqudens")
