// #include <gtest/gtest.h>
// #include <bptree.hpp>
// #include <memory>
// #include <vector>
// #include <set>

// class NonLeafFixture : public ::testing::Test
// {
// protected:
//   struct Record;
//   using Key = int;
//   static constexpr size_t M = 5;

//   NonLeafFixture()
//       : keys{
//             10,
//             20,
//             40,
//             80,
//             160,
//             15,
//             30,
//             60,
//             120,
//             12,
//             24,
//             48,
//             96,
//         } {};

//   auto SetUp() -> void override
//   {
//     keys = std::vector<Key>{keys.begin(), keys.begin() + M};
//   }
//   auto TearDown() -> void override
//   {
//   }

//   bptree::NonLeafNode<Key, Record, M> nonleafNode;
//   std::vector<Key> keys;
// };

// TEST_F(NonLeafFixture, KeySizeWhenInsert)
// {
//   EXPECT_TRUE(nonleafNode.empty());
//   size_t cnt = 0;
//   for (const auto &k : keys)
//   {
//     nonleafNode.insert(k);
//     EXPECT_EQ(nonleafNode.keyCount(), ++cnt);
//   }
//   EXPECT_TRUE(nonleafNode.full());
// }