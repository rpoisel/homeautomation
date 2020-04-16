add_executable(cellar
  user.cpp
)

target_link_libraries(cellar
  IO
  PLC
  ${CONAN_LIBS}
)

install(TARGETS cellar RUNTIME DESTINATION bin)
