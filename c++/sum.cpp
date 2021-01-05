/*
 * Chapter10. Exercise1. 
 * Write a program that produces the sum of all the numbers
 * in a file of whitespace-seperated integers
 * 
 */

#include "std_lib_facilities.h"

int sum_int(istream&);
int mul_int(istream&);
int cal_int(istream&, int (*oper)(int, int));
int get_int(istream&);
void next_int(istream&);
int sum(int, int);
int mul(int, int);

int main(void) 
{
    ifstream fs{"mydata.txt"};
    if (!fs) error("couldn't find file");
    //for (char ch = 0; fs; ch = fs.get()) cout << ch;
    //cout << endl;
    cout << sum_int(fs) << endl;
    fs = ifstream{"mydata.txt"};
    cout << mul_int(fs) << endl;
    fs = ifstream{"mydata.txt"};
    cout << cal_int(fs, sum) << endl;
    fs = ifstream{"mydata.txt"};
    cout << cal_int(fs, mul) << endl;
    return 0;
}

int sum_int(istream& is) {
    int ret = 0;
    for (int tmp; true; ) {
        tmp = get_int(is);
        if (is.eof()) {
            ret += tmp;
            break;
        }
        if (is.fail()) next_int(is);
        if (is.bad()) error("try to fix streamfile.");
        ret += tmp;
    }
    return ret;
}
int mul_int(istream& is) {
    int ret = 1;
    for (int tmp; true;) {
        tmp = get_int(is);
        if (is.eof()) {
            ret *= tmp;
            break;
        }
        if (is.fail()) {
            next_int(is);
            continue;
        }
        if (is.bad()) error("sorry I cannot fix it");
        ret *= tmp;
    }
    return ret;
}
int cal_int(istream& is, int (*oper)(int, int)) {
    int ret = get_int(is);
    if (!is) error ("no file");
    for (int tmp; true;) {
        tmp = get_int(is);
        if (is.eof()) {
            ret = oper(ret, tmp);
            break;
        }
        if (is.fail()) {
            next_int(is);
            continue;
        }
        if (is.bad()) error ("sorry I cannot handle it");
        ret = oper(ret, tmp);
    }
    return ret;
}
int get_int(istream& is) {
    int ret;
    is >> ret;
    return ret;
}
void next_int(istream& is) {
    // eof handle require
    is.clear();
    for (char ch = 0; (!isdigit(ch) && is); ch = is.get()) {
        //cout << "skipped : " << ch << endl;
    }
    if (is.eof()) return;
    is.unget();
}
int sum(int a, int b) {
    return a + b;
}
int mul(int a, int b) {
     return a * b;
}