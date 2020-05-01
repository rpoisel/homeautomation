add_library(Arduino STATIC
  Arduino.cpp
)

target_include_directories(Arduino PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

