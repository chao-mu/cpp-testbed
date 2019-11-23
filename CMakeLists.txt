cmake_minimum_required(VERSION 3.10)
project(loexp)

option(COVERAGE "Enable code coverage reporting" FALSE)

if (COVERAGE)
    # Disable code optimizations
    add_compile_options(--coverage -O0)
    MESSAGE(STATUS "Coverage enabled!")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")

#
# Conan (Dependency Management) fun!
#
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
                  "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_check(VERSION 1.0.0 REQUIRED)

conan_add_remote(
    NAME vidrevolt
    URL https://api.bintray.com/conan/vidrevolt/conan-packages
)

set (CONAN_SETTINGS SETTINGS compiler.libcxx=libstdc++11)
conan_cmake_run(
    REQUIRES
        liblo/0.30@vidrevolt/stable
        sol/3.0.3@vidrevolt/stable
        gtest/1.8.1@bincrafters/stable
    BASIC_SETUP
        ${CONAN_SETTINGS}
    BUILD missing
)

add_executable(${PROJECT_NAME} src/main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wextra" "-Wall")
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} --coverage)

#
# Testing!
#
enable_testing()

add_executable(tests test/main.cpp)
include(GoogleTest)
gtest_discover_tests(tests)
target_compile_options(tests PRIVATE "-Wextra" "-Wall")
target_link_libraries(tests ${CONAN_LIBS})
target_link_libraries(tests --coverage)
