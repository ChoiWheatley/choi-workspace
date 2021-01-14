/*
 * <PPPUC++> Chapter11 Exercise9
 * This program reads text file and converts into binary file.
 */
#include "std_lib_facilities.h"

int main(void) {
    ifstream ifs{"penguin.jpg"};
    ofstream ofs{"output.jpg", ios_base::binary};
    vector<char> v;
    for (char x; true; v.push_back(x)) {
        x = ifs.get();
        if (x == 'N') x = 'n';
        if (x == 'X') x = 'x';
        if (x == 'A') x = 'a';
        if (ifs.eof()) {
            v.push_back(x);
            break;
        }
        else if (ifs.fail()) continue;
        else if (ifs.bad()) error("error in reading file");
    }

    //debug
    /*
    for (auto x : v) {
        static int cnt = 0;
        cout << x << ' ';
        if ((++cnt %20) == 0) cout << '\n';
    }
    */
    // write binary from text
    for (int x = 0; x < v.size(); x++) {
        ofs.write(as_bytes(v[x]), sizeof(char));
    }
    return 0;
}