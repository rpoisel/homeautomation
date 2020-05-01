add_subdirectory(lib)

add_library(TestMain STATIC
  test_main.cpp
)

target_link_libraries(TestMain PUBLIC Catch2::Catch2)

### BitHelpers
add_executable(test_bithelpers_app
  test_bithelpers.cpp
)

target_link_libraries(test_bithelpers_app PRIVATE
  BitHelpers
  TestMain
)

add_test(NAME test_bithelpers COMMAND test_bithelpers_app)

### PLC
add_executable(test_plc_app
  test_plc.cpp
)

target_link_libraries(test_plc_app PRIVATE
  PLC
  TestMain
)

add_test(NAME test_plc COMMAND test_plc_app)