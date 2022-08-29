#ifndef KEYRECORD
#define KEYRECORD

#include <bptree.hpp>
#include <string>

using std::string;

// unique key
using Key = uint32_t;
enum Grade
{
  Freshman = 1,
  Sophomore = 2,
  Junior = 3,
  Senior = 4,
};
template <class Key>
struct RecordImpl : public bptree::Record<Key>
{
  auto key() -> Key override { return Key{id}; };

  uint32_t id;
  string name;
  Grade grade;

  ~RecordImpl() override{};
  RecordImpl(uint32_t id, const string &name, Grade grade)
      : id{id}, name{name}, grade{grade} {};
  RecordImpl(const RecordImpl &other) = default;
  RecordImpl(RecordImpl &&other) = default;

  auto operator=(RecordImpl other) -> RecordImpl &;
  auto operator=(const RecordImpl &other) -> RecordImpl & = default;
  auto operator=(RecordImpl &&other) -> RecordImpl & = default;
};

// implementations
template <class Key>
auto RecordImpl<Key>::operator=(RecordImpl<Key> other) -> RecordImpl<Key> &
{
  id = other.id;
  name = other.name;
  grade = other.grade;
  return *this;
}

#endif // KEYRECORD