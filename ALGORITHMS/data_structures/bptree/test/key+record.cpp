#include <bptree.hpp>
#include <string>

namespace mytest
{
  using std::string;

  // unique key
  struct Key
  {
    uint32_t id;
  };

  template <class Key>
  struct Record_ : public bptree::Record<Key>
  {
    auto key() -> Key override;

    Key id;
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
    Record_(Key id, const string &name, Gender gender, uint32_t score, Grade grade)
        : id{id}, name{name}, gender{gender}, score{score}, grade{grade} {};
    Record_(const Record_ &other) = default;
    Record_(Record_ &&other) = default;

    auto operator=(Record_ other) -> Record_ &;
    auto operator=(const Record_ &other) -> Record_ & = default;
    auto operator=(Record_ &&other) -> Record_ & = default;
  };

  // implementations
  using R = Record_<Key>;

  template <>
  auto R::key() -> Key { return id; }

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
} // namespace mytest