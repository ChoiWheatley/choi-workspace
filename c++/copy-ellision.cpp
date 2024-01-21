#include <iostream>
struct C {
    C() {}
    C(const C &) { std::cout << "A copy was made.\n"; }
};

C f() {
    return C(); // Definitely performs copy elision
}
C g() {
    C c;
    return c; // Maybe performs copy elision
}

int main() {
    std::cout << "Hello World!\n";
    C obj = f(); // Copy constructor isn't called
    C obj2 = g();
}