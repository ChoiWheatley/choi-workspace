/// https://www.programiz.com/dsa/b-plus-tree
#include <algorithm>
#include <climits>
#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <array>
#include <memory>

using std::array;
using std::shared_ptr;

using namespace std;

static constexpr int MAX = 3;
static constexpr int EMPTY = -1;

struct Record;

template <typename T> class AbstractNode {
  bool isLeaf;
  array<T, MAX> keys;
  friend class BPTree;

public:
  AbstractNode<T>() : keys{std::array<T, MAX>{}.fill(EMPTY)} {}
};

template <typename T> class InternalNode : AbstractNode<T> {
  // bool isLeaf;
  // array<T, MAX> keys;
  array<shared_ptr<AbstractNode<T>>, MAX + 1> points;

public:
  auto keySize() const -> int;
};

template<typename T> class LeafNode : AbstractNode<T> {
  bool isLeaf;
  array<T, MAX> keys;
  array<shared_ptr<Record>, MAX + 1> points;

public:

};

// class Node {
//   bool isLeaf;
//   int * key;
//   int size;
//   Node **ptr;
//   friend class BPTree;
// public:
//   Node();
// };

class BPTree {
  Node *root;
  void insertInternal(int, Node *, Node *);
  Node *findParent(Node *, Node *);

  public:
  BPTree();
  void search(int);
  void insert(int);
  void display(Node *);
  Node *getRoot();
};

Node::Node() {
  key = new int[MAX];
  ptr = new Node*[MAX+1];
}

BPTree::BPTree() {
  root = nullptr;
}

void BPTree::search(int x) {
  if (root == nullptr) {
    throw runtime_error("tree is empty");
  }
  Node * cursor = root;
  while (!cursor->isLeaf) {

  }
}
