add_library(hardware STATIC
  Arduino.cpp
  Wire.cpp
)

target_include_directories(hardware PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)
