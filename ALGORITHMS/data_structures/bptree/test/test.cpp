#include "key_record.hpp"
#include "real_factory.hpp"
#include <gtest/gtest.h>

TEST(Init, ForBetterCompilation)
{
  constexpr size_t M = 3;

  const auto realFactory = RealFactory<Key>{};
  const auto bpt = realFactory.makeTree(M);
  NodeImpl<Key> node(Has::RecordPointers);
}