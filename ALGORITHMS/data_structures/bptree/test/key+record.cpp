#include <bptree.hpp>
#include <string>

using bptree::Key;
using std::string;

// unique key
struct Key_ : public bptree::Key
{
  uint32_t id;
};

struct Record_ : public bptree::Record
{
  auto key() -> Key * override;

  Key_ id;
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

  ~Record_() override{};
  Record_(Key_ id, const string &name, Gender gender, uint32_t score, Grade grade)
      : id{id}, name{name}, gender{gender}, score{score}, grade{grade} {};
  Record_(const Record_ &other) = default;
  Record_(Record_ &&other) = default;

  auto operator=(Record_ other) -> Record_ &;
  auto operator=(const Record_ &other) -> Record_ & = default;
  auto operator=(Record_ &&other) -> Record_ & = default;
};

// implementations

auto Record_::key() -> Key * { return &id; }

auto Record_::operator=(Record_ other) -> Record_ &
{
  id = other.id;
  name = other.name;
  gender = other.gender;
  score = other.score;
  grade = other.grade;
  return *this;
}