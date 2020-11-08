/*
Chapter 8 Drill 1
*/

#include "my.h"
extern int my_foo;

int main(void)
{
    my_foo = 7;
    print_foo();
    my_foo = 100;
    print_foo();

    print(99);

    return 0;
}