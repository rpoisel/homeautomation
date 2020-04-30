add_subdirectory(lib/Catch2)

add_library(TestMain STATIC
  test_main.cpp
)

target_link_libraries(TestMain PUBLIC Catch2::Catch2)

add_executable(test_bithelpers_app
  test_bithelpers.cpp
)

target_link_libraries(test_bithelpers_app PRIVATE
  BitHelpers
  TestMain
)

add_test(NAME test_bithelpers COMMAND test_bithelpers_app)