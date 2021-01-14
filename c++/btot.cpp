/* 
 * <PPPUC++> Chapter11 Exercise9
 * This program Converts an text file into binary file
 * refer to 11.3.2 Binary Files, 
 *      "istream reads a sequence of characters and turns into a object of desired type"
 *      "ostream takes an object of a specified type and transforms it into a sequence of 
 *       charactors which it write out."
 * 
 * // read from binary file;
 * for (int x; is.read(as_bytes(x), sizeof(int));)
 *      v.push_back(x);
 * 
 * // write to binary file;
 * for (int x : v) 
 *      os.write(as_bytes(x), sizeof(int));
 * 
 * read(1, 2), write(1, 2)
 * 1 : First pointer of sequence of data
 * 2 : How quantity of each size is
 * 
 * << First Attempt 21. 1. 14 >>
 */

#include "std_lib_facilities.h"



int main(void) {
    ifstream ifs{"penguin.jpg", ios_base::binary};
    ofstream ofs{"output.txt"};
    if (!ifs || !ofs) error("error opening the file");
    vector<char> v;

    for (char x; ifs.read(as_bytes(x), sizeof(x));)
        v.push_back(x);
    
    for (auto x : v) {
        ofs << x;
    }
    return 0;
}