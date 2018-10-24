cmake_minimum_required(VERSION 3.10)
project(homeautomation)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(CPack)

add_subdirectory(hardware)
add_subdirectory(io)
add_subdirectory(plc)

add_executable(homeautomation
  user.cpp
)

target_include_directories(homeautomation PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(homeautomation PUBLIC
  IO
  PLC
  ${CONAN_LIBS}
)

add_custom_target(docker
  COMMAND docker --version
)

add_dependencies(docker package)
