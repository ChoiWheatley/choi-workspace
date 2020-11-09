/*
Chapter 8 Drill 1
*/

#include "my.h"

int my_foo = 0;
int main(void)
{
    my_foo = 7;
    print_foo();
    my_foo = 100;
    print_foo();

    print(99);

    return 0;
}