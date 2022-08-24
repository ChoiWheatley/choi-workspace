#include "key_record.hpp"
#include "real_factory.hpp"
#include <gtest/gtest.h>

TEST(Init, ForBetterCompilation)
{
  constexpr size_t M = 3;
  const vector<R> records{
      R{1, "name", R::Male, 100, R::Freshman},
      R{2, "name1", R::Female, 200, R::Freshman},
      R{3, "name2", R::Male, 300, R::Freshman},
      R{4, "name3", R::Female, 400, R::Freshman},
      R{5, "name4", R::Male, 500, R::Freshman},
      R{6, "name5", R::Female, 600, R::Freshman},
  };
  // auto record = RecordImpl<Key>{1, "name", R::Male, 100, R::Freshman};

  const auto realFactory = RealFactory<Key>{};
  const auto bpt = realFactory.makeTree(M);
  NodeImpl<Key> node(Has::RecordPointers);

  for (const auto &r : records)
  {
    bpt->Add(std::make_unique<R>(r));
  }

  bpt->Find(Key{1});

  bpt->Delete(Key{1});
}