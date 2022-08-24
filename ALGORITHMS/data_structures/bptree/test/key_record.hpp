#ifndef KEYRECORD
#define KEYRECORD

#include <bptree.hpp>
#include <string>

using std::string;

// unique key
struct Key
{
  uint32_t id;
};

template <class Key>
struct RecordImpl : public bptree::Record<Key>
{
  auto key() -> Key override { return Key{id}; };

  uint32_t id;
  string name;
  enum Gender
  {
    Male = 0,
    Female = 1,
    Other = 2,
  } gender;
  uint32_t score;
  enum Grade
  {
    Freshman = 1,
    Sophomore = 2,
    Junior = 3,
    Senior = 4,
  } grade;

  ~RecordImpl() override{};
  RecordImpl(uint32_t id, const string &name, Gender gender, uint32_t score, Grade grade)
      : id{id}, name{name}, gender{gender}, score{score}, grade{grade} {};
  RecordImpl(const RecordImpl &other) = default;
  RecordImpl(RecordImpl &&other) = default;

  auto operator=(RecordImpl other) -> RecordImpl &;
  auto operator=(const RecordImpl &other) -> RecordImpl & = default;
  auto operator=(RecordImpl &&other) -> RecordImpl & = default;
};

// implementations
using R = RecordImpl<Key>;

template <>
auto R::operator=(R other) -> R &
{
  id = other.id;
  name = other.name;
  gender = other.gender;
  score = other.score;
  grade = other.grade;
  return *this;
}

#endif // KEYRECORD