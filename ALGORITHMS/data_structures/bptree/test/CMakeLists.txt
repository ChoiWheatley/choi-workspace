enable_testing()

add_executable(${TEST_TARGET}
  test.cpp
  test_helper.cpp
  real_factory.hpp
  key_record.hpp
  stacktest.cpp
)

target_link_libraries(${TEST_TARGET}
  PUBLIC GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})