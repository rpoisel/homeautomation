add_subdirectory(cellar)
add_subdirectory(groundfloor)

add_custom_target(docker
  COMMAND docker --version
)

add_dependencies(docker package)

