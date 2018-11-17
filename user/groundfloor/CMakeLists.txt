add_executable(groundfloor
  user.cpp
)

target_link_libraries(groundfloor
  IO
  PLC
  ${CONAN_LIBS}
)

# the following is due to the standard compliance of paho-cpp headers
set_property(TARGET groundfloor PROPERTY CXX_STANDARD 14)

install(TARGETS groundfloor RUNTIME DESTINATION bin)

