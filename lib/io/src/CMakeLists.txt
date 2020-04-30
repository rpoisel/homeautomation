add_library(IO STATIC
  PCF8574.cpp
)

target_include_directories(IO PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(IO PUBLIC
  BitHelpers
  Arduino
)
