/*
  https://swexpertacademy.com/main/talk/codeBattle/problemDetail.do?contestProbId=AYHSSFs6AcgDFATO&categoryId=AYHWVZMqQWEDFATO&categoryType=BATTLE&battleMainPageIndex=1

  <mId, mGrade, mGender, mScore> 레코드를 정의, 바뀔 일 없다.
  레코드는 기본적으로 mId에 대하여 정렬이 되어있다.

  인덱스는 이진트리를 활용하여 각 attribute에 대하여 인덱싱을 수행한다.
  나무의 모양을 고르게 하기 위해 b+tree의 개념을 참조한다.

*/
#include <vector>
#include <set>

constexpr unsigned int MAX_ID = 1000000001;
constexpr unsigned int MAX_SCORE = 300001;
constexpr unsigned int MAX_GRADE = 4;
constexpr char MALE[7] = "male";
constexpr char FEMALE[7] = "female";

typedef int Idx;

struct Record {
  Idx mId;          /* 1 <= mId <= 1,000,000,000 */
  int mGrade;       /* 1 <= mGrade <= 3 */
  char mGender[7];  /* "male" or "female" */
  int mScore;       /* 0 <= mScore <= 300,000 */

  auto operator<(const Record& other) -> bool {
    return (this->mId < other.mId);
  }
};

template <typename T> class Node {
public:
  Node(T key) : key{key} {}
  auto left() -> Node<T> * { return this->_left; }
  auto right() -> Node<T> * { return this->_right; }
  auto record() -> Record * { return this->_record; }

private:
  const T key;
  Node<T> *_left;
  Node<T> *_right;
  Record *_record;
};

template <typename T> class Index {
private:
  Node<T> root;
};

class DataBase {
public:
  std::set<Record> records; /* sorted by mId */

  int add(int mId, int mGrade, char mGender[7], int mScore) { return 0; }

  int remove(int mId) { return 0; }

  int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7],
            int mScore) const {
    return 0;
  }

  DataBase() {}

private:
  // TODO: mGrade에 대한 인덱스
  // TODO: mScore에 대한 인덱스
};

void init() {
  return;
}

int add(int mId, int mGrade, char mGender[7], int mScore) { return 0; }

int remove(int mId) { return 0; }

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7],
          int mScore) {
  return 0;
}