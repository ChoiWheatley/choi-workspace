/*
 * <PPPUC++> Chapter 11 Exercise1
 * 
 * Write a program that reads a text file and coverts its input to all lower case,
 * producing a new file.
 */

#include "std_lib_facilities.h"

enum class ERRCODE {
    good,
    bad_stream,
    fail,
};

void tolowercase(string& s);
ERRCODE read_and_out(istream&, ostream&);

int main() {
    string input, output;
    // cout << "please input name of original text file : \n>>>";
    //cin >> input;
    //cout << "please input name of processed text file : \n>>>";
    //cin >> output;
    ifstream is{"original.txt"};
    ofstream os{"processed.txt"};
    if (!is) error ("cannot open file :");
    if (!os) error ("cannot open file :");

    switch(read_and_out(is, os)) {
        case ERRCODE::good :
            return 0;
        case ERRCODE::fail :
            error("something was wrong with it.");
            break;
        case ERRCODE::bad_stream :
            error("bad stream");
            break;
    }
    

    return 0;
}











void tolowercase(string& s) {
    for (char& i : s) i = tolower(i);
}
ERRCODE read_and_out(istream& is, ostream& os) {
    for (char str; true; ) {
        str = is.get();
        str = tolower(str);
        // is error handleing
        if (is.eof()) {
            break;
        }
        else if (is.fail()) {// maybe some format error?
            return ERRCODE::fail;
        }
        else if (is.bad()) return ERRCODE::bad_stream;
        
        // os error handleing
        if (os.fail()) return ERRCODE::fail;
        else if (os.bad()) return ERRCODE::bad_stream;

        os.put(str);
    }
    return ERRCODE::good;
}