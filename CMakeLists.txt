cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.10)
project(homeautomation VERSION 0.9.9)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(CPack)

add_subdirectory(arduino)
add_subdirectory(lib/io/src)
add_subdirectory(lib/plc/src)
add_subdirectory(src)
