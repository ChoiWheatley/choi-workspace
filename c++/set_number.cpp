/* 
 * <PPPUC++> Chapter11 Exercise2
 * Write a program that given a file name and a word output each line that contains
 * that word together with the line number.
 * 
 */

#include "std_lib_facilities.h"

enum class ERRCODE {
    good,
    eof,
    fail,
    bad
};
ERRCODE get_and_set(istream&, ostream&);

int main() {
    string origin = "original.txt", proc = "processed.txt";
    ifstream is{origin};
    ofstream os{proc};
    if (!is || !os) error ("something wrong with opening file", origin + proc);
    switch(get_and_set(is, os)) {
        case ERRCODE::good:
        case ERRCODE::eof:
            break;
        case ERRCODE::fail:
            error("something wrong with formatting from and to files");
            break;
        case ERRCODE::bad:
            error("Serious problem occured. exit this program");
            break;
    }

    return 0;
}

// using getline() function
ERRCODE get_and_set(istream& is, ostream& os) {
    int count = 1;
    for (string str; true; count++) {
        getline(is, str);
        // is error handling
        if (is.eof()) {
            str = to_string(count) + "\t" + str;
            os << str;
            return ERRCODE::eof;
        }
        else if (is.fail()) return ERRCODE::fail;      // no worth of skipping to next line
        else if (is.bad()) return ERRCODE::bad;

        //os error handling
        if (os.fail()) return ERRCODE::fail;
        else if (os.bad()) return ERRCODE::bad;

        // concatenating
        str = to_string(count) + "\t" + str;
        os << str << '\n';
    }
    return ERRCODE::good;
}