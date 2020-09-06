#include <iostream>
#include <string>
using namespace std;

class MyClass
{
private:
    std::string name_;
    int age_;

public:
    MyClass(std::string, int);
    MyClass(const MyClass &);
    ~MyClass();
    std::string getName();
    int getAge();
};

std::string MyClass::getName()
{
    return (this->name_);
}
int MyClass::getAge()
{
    return (this->age_);
}
MyClass::MyClass(std::string name, int age)
{
    name_ = name;
    age_ = age;
}
MyClass::MyClass(const MyClass &origin)
{
    name_ = origin.name_;
    age_ = origin.age_;
}
MyClass::~MyClass()
{
    cout << "소멸자가 호출되었ㅅ";
}

int main(void)
{
    MyClass my1("최승현", 24);
    MyClass *my2 = new MyClass(my1); //복사생성자를 사용, deep copy
    MyClass my3 = my1;               //대입연산자를 사용, shallow copy

    cout << my2->getName() << endl;
    cout << "my1의 주소 : " << &my1 << " / my2의 주소 : " << my2 << " / my3의 주소 : " << &my3 << endl;

    delete my2;

    return 0;
}