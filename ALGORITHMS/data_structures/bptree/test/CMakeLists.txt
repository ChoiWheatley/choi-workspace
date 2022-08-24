enable_testing()

add_executable(${TEST_TARGET}
  key+record.hpp
  test.cpp
)

target_link_libraries(${TEST_TARGET}
  PUBLIC GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})