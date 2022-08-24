#include "key+record.hpp"
#include <bptree.hpp>
#include <gtest/gtest.h>

using namespace bptree;

TEST(Init, ForBetterCompilation)
{
  BPTreeImpl<Key> bpt;
  NodeImpl<Key> node(Has::RecordPointers);
}