#include "helpers.hpp"
#include "key_record.hpp"
#include "real_factory.hpp"
#include <bptree.hpp>
#include <gtest/gtest.h>
#include <tuple>

TEST(Init, ForBetterCompilation)
{
  using R = RecordImpl<Key>;

  constexpr size_t M = 3;
  const vector<R> records{
      R{1, "name", Freshman},
      R{2, "name1", Freshman},
      R{3, "name2", Freshman},
      R{4, "name3", Freshman},
      R{5, "name4", Freshman},
      R{6, "name5", Freshman},
  };
  // auto record = RecordImpl<Key>{1, "name", R::Male, 100, R::Freshman};

  const auto realFactory = RealFactory<Key>{};
  const auto bpt = realFactory.makeTree(M);

  for (const auto &r : records)
  {
    bpt->Add(std::make_unique<R>(r));
  }

  bpt->Find(Key{1});

  bpt->Delete(Key{1});
}