add_executable(cellar
  user.cpp
)

target_link_libraries(cellar
  IO
  PLC
)

install(TARGETS cellar RUNTIME DESTINATION bin)
