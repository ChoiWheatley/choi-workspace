/* 
 * <PPPUC++> Chapter11 Exercise12
 * Recverse the order of characters in a text file.
 * 
 * << First Attempt 2021. 01. 14. >>
 * find out the index number of eof()
 * 
 */
#include "std_lib_facilities.h"

int main() {
    ifstream ifs{"sample.txt"};
    ofstream ofs{"output.txt"};
    if (!ifs || !ofs) error("error opening files");
    // find out the position of eof()
    int eof_pos = 0;
    for (; true; eof_pos++) {
        ifs.get();
        if (ifs.eof()) {
            break;
        } else if (ifs.fail()) {
            continue;
        } else if (ifs.bad()) {
            error ("something bad occured");
        }
    }
    ifs = ifstream{"sample.txt"};
    for (char c; eof_pos > 0; ) {
        ifs.seekg(--eof_pos);
        c = ifs.get();
        ofs.put(c);
    }

    return 0;
}