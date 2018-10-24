add_library(PLC STATIC
  PLC.cpp
)

target_include_directories(PLC PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(PLC PUBLIC
  rt
)
