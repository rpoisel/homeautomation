add_executable(cellar
  cellar.cpp
)

target_link_libraries(cellar
  IO
  PLC
  ${CONAN_LIBS}
)

install(TARGETS cellar RUNTIME DESTINATION bin)

# these dependencies / new targets had to be added here
# adding them in another subdirectory lead to an empty
# package (created by CPack)
add_custom_target(docker
  COMMAND docker --version
)

add_dependencies(docker package)

