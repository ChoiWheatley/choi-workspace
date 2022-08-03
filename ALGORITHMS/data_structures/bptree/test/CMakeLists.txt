enable_testing()

add_executable(${TEST_TARGET}
  test_bptree.cpp
  test_placement_new.cpp
  test_is_same.cpp
  test_shared_ptr.cpp
  test_std_array.cpp
  test_leaf_node.cpp
  test_nonleaf_node.cpp
)

target_link_libraries(${TEST_TARGET}
  PUBLIC GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(${TEST_TARGET})