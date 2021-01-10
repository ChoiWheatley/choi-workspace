/* 
 * <PPPUC++> Chapter11 Exercise3
 * Write a program that removes all vowels from a file.
 * For example, "Once upon a time!" becomes "nc pn tm!"
 */

#include "std_lib_facilities.h"

const vector<char> vowels{
    'a', 'e', 'i', 'o', 'u'
};
enum class ERRCODE {
    good,
    eof,
    fail,
    bad
};

bool is_vowel(char c);
ERRCODE get_and_put(istream&, ostream&);

int main() {
    ifstream is{"original.txt"};
    ofstream os{"processed.txt"};
    if (!is || !os) error("opening file error occured!");
    switch(get_and_put(is, os)) {
        case ERRCODE::good:
        case ERRCODE::eof:
            break;
        case ERRCODE::bad:
            error("something went wrong!");
            return 1;
    }
    return 0;
}





bool is_vowel(char c) {
    for (auto i : vowels) if (i == c) return true;
    return false;
}
ERRCODE get_and_put(istream& is, ostream& os) {
    for (char c; true; ) {
        c = is.get();
        // is error handling
        if (is.eof()) {
            return ERRCODE::eof;
        }
        else if (is.fail()) ; // there is nothing to deal with it.
        else if (is.bad()) return ERRCODE::bad;

        if (is_vowel(c)) continue;
        os.put(c);
        // os error handling
        if (os.bad()) return ERRCODE::bad; 
    }
    return ERRCODE::good;
}