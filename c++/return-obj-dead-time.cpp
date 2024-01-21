#include <iostream>

using namespace std;

class SoSimple {
  private:
    int num;

  public:
    SoSimple(int n) : num(n) { std::cout << "New Object: " << this << endl; }
    SoSimple(const SoSimple &copy) : num(copy.num) {
        std::cout << "New Copy obj" << this << endl;
    }
    explicit SoSimple(SoSimple &&mv) : num(std::move(mv.num)) {
        std::cout << "Move obj" << this << endl;
    }
    ~SoSimple() { std::cout << "Destroy obj" << this << endl; }
};

SoSimple SimpleFuncObj(SoSimple ob) {
    std::cout << "Parm ADR:" << &ob << endl;
    return ob;
}
int main(void) {
    SoSimple obj(7);
    SimpleFuncObj(obj);
    std::cout << endl;
    SoSimple &&tempRef = SimpleFuncObj(obj);
    std::cout << "Return Obj " << &tempRef << endl;
    return 0;
}