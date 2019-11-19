cmake_minimum_required(VERSION 3.10)
project(loexp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

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
    BASIC_SETUP
        ${CONAN_SETTINGS}
    BUILD missing
)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE "-Wextra" "-Wall" "-pedantic-errors")

# Libraries brought in by conan dependency manager
target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
