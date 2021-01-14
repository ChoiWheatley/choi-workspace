/*
 * <PPPUC++> Chapter11 Exercise10 & 11
 * - Write a function vector<string> split(const string& s) that returns a vector of
 * whitespace-separated substrings from the argument s.
 * 
 * - Also write a function vector<string> split(const string& s, const string& w) that
 * returns a vector of whitespace-separated from the arguments s, where whitespace is
 * defined as "ordinary whitespace" plus the characters in w.
 * 
 */

#include "std_lib_facilities.h"

vector<string> split(const string& s);
vector<string> split(const string& s, const string& w);

int main() {
    ifstream ifs{"sample.txt"};
    ofstream ofs{"output.txt"};
    if (!ifs) error ("error opening and initializing file");
    // stream ===> string
    string sample;
    for (char ch; true; sample += ch) {
        ch = ifs.get();
        if (ifs.eof()) {
            sample += ch;
            break;
        } else if (ifs.fail()) {
            continue;
        } else if (ifs.bad()) {
            error ("something badbit");
        }
    }

    // string ===> separate strings
    vector<string> sepa;
    sepa = split(sample);
    for (auto i : sepa) {
        static int cnt = 0;
        ofs << setw(15) << i;
        if ((++cnt %10) == 0) ofs << '\n';
    }
    ofs << "\n\n";

    // string ===> user defined separator 
    string separator = "aeiou";
    sepa = split(sample, separator);
    for (auto i : sepa) {
        static int cnt = 0;
        ofs << setw(15) << i;
        if ((++cnt %10) == 0) ofs << '\n';
    }
    return 0;
}
vector<string> split(const string& s) {
    vector<string> ret;
    string buffer;
    for (char c : s) {
        if (iswspace(c)) {
            c = ' ';
            buffer += c;
            ret.push_back(buffer);
            buffer = "";
        }
        buffer += c;
    }
    ret.push_back(buffer);
    return ret;
}
vector<string> split(const string& s, const string& w) {
    vector<string> ret;
    string buffer;
    for (char c : s) {
        if (iswspace(c) || w.find(tolower(c)) != string::npos) {
            c = ' ';
            buffer += c;
            ret.push_back(buffer);
            buffer = "";
        }
        buffer += c;
    }
    ret.push_back(buffer);
    return ret;
}