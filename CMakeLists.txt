cmake_minimum_required(VERSION 3.10)
project(homeautomation-rpo)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(hardware)

add_executable(homeautomation
  user.cpp
)

target_include_directories(homeautomation PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(homeautomation PUBLIC
  hardware
)
