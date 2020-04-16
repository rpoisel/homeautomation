add_library(Arduino STATIC
  Arduino.cpp
  Wire.cpp
)

target_include_directories(Arduino PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
