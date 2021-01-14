/* 
 * <PPPUC++> Chapter11 Exercise13
 *  Reverse the order of words (defined as whitespace-separated strings) in a file.
 * For example, "Norwegian Blue parrot" ==> "parrot Blue Norwegian". You are allowed 
 * to assume that all the strings from the file will fit into memory at once.
 */

#include "std_lib_facilities.h"

vector<string> get_words(istream&);

int main() {
    ifstream ifs{"sample.txt"};
    ofstream ofs("output.txt");
    if (!ifs || !ofs) error("something error happened during opening files");
    vector<string> words = get_words(ifs);
    for (int i = words.size()-1; i >= 0; i--) {
        ofs << words[i];
    }
    return 0;
}
vector<string> get_words(istream& is) {
    vector<string> ret;
    string buffer;
    for (char ch; true; ) {
        ch = is.get();
        if (iswspace(ch)) {
            ret.push_back(buffer);
            ret.push_back(to_string(ch));
            buffer = "";
            continue;
        }
        if (is.eof()) {
            ret.push_back(buffer);
            break;
        } else if (is.fail()) {
            continue;
        } else if (is.bad()) {
            error("something bad happend");
        }
        buffer += ch;
    }
    return ret;
}