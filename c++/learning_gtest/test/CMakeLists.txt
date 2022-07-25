enable_testing()

add_executable(
  ${MY_TEST_TARGET}
  hello_test.cc
  test_mymain.cpp
  test_queue.cpp
)
target_link_libraries(${MY_TEST_TARGET}
  PUBLIC GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${MY_TEST_TARGET})