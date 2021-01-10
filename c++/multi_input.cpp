/*
 * <PPPUC++> Chapter11 Exercise4
 * Write a program that prompts the user to enter several integers in any combination of
 * octal, decinal, or hexadecimal, using the '0' and '0x' base suffixes. 
 * interprets the numbers correctly; and onverts them to decimal form.
 * Then your program shoud output the values in properly spaced columns lik this :
 * 
 * 0x43  hexadecimal converts to     67  decimal
 * 0123  octal       converts to     83  decimal
 *   65  decimal     converts to     65  decimal
 * 
 * 
 * 1. string 으로 처묵 및 vector<string> 에 저장
 * 2. istringstream 으로 read 및 vector<int> 에 저장
 * 3. cout format print
 */

#include "std_lib_facilities.h"

enum class ERRCODE {
    good,
    eof,
    fail,
    format,
    bad
};
enum class M_base {
    octal,
    decimal,
    hexadecimal
};
vector<string> m_base {
    "octal",
    "decimal",
    "hexadecimal"
};

struct M_input {
    vector<string> original;
    vector<int> converted;
};

constexpr char Cmd_exit = '|';

M_input prompt();
vector<string> input(istream&);
vector<int> output(const vector<string>&);
ostream& operator<<(ostream& os, const M_input& m);
int longest_string(const vector<string>&);
int longest_int(const vector<int>&);
M_base base(const string&);

int main(void) 
{
    try{
        cout << prompt() << '\n';
    }
    catch(ERRCODE e) {
        switch(e) {
            case ERRCODE::fail:
                error("we met failbit when trying to find terminating charactor, ", Cmd_exit);
                return 1;
            case ERRCODE::bad:
                error("we couldn't find an answer to get rid of thie problem");
                return 1;
        }
    }
    return 0;
}


M_input prompt() {
    cout << "Please input several numbers including base suffices.\nthe exit command is '|'.\n>>>";
    vector<string>  original  = input(cin);
    vector<int>     converted = output(original);
    return M_input{original, converted};
}
vector<string> input(istream& is) {
    vector<string> ret;
    for (char terminator; true; ) {
        is >> terminator;
        // is error handling
        if (is.good() && terminator == Cmd_exit) break;
        else if (is.eof()) break;                   // regard as we met Cmd_exit
        else if (is.fail()) throw ERRCODE::fail;    // we mustn't fail while we got one character
        else if (is.bad()) throw ERRCODE::bad;      // we cannot handle this problem

        is.unget();
        string newnum;
        is >> newnum;
        // is error handling
        if (is.eof()) break;                        // regard as we met Cmd_exit
        else if (is.fail()) continue;               // skip to next string
        else if (is.bad()) throw ERRCODE::bad;      // we cannot handle this
        ret.push_back(newnum);
    }
    return ret;
}
vector<int> output(const vector<string>& origin) {
    vector<int> ret;
    for (auto i : origin) {
        istringstream istr{i};
        istr.unsetf(ios::dec | ios::hex | ios::oct);
        int newnum = 0;
        istr >> newnum;
        ret.push_back(newnum);
    }
    return ret;
}
ostream& operator<<(ostream& os, const M_input& m) {
/*
 * :::::: Sample Example ::::::
 * 0x43  hexadecimal converts to     67  decimal
 * 0123  octal       converts to     83  decimal
 *   65  decimal     converts to     65  decimal
 */
    int longest_origin = 0, longest_converted = 0;
    longest_origin = longest_string(m.original);
    longest_converted = longest_int(m.converted);
    for (int i = 0; i < m.original.size(); i++) {
        os << setw(longest_origin + 3) << right << m.original[i]  << " " <<
                setw(string("hexadecimal").size() + 3) << left << m_base[static_cast<int>(base(m.original[i]))] <<  " " << 
                "converts to\t" << 
                setw(longest_converted + 3) << m.converted[i] << " " <<
                "decimal\n";
    }
    return os;
}
int longest_string(const vector<string>& v) {
    int ret = 0;
    for (auto i : v) {
        if (ret < i.size()) ret = i.size();
    }
    return ret;
}
int longest_int(const vector<int>& v) {
    int ret = 0;
    for (auto i : v) {
        if (ret < to_string(i).size()) ret = to_string(i).size();
    }
    return ret;
}
M_base base(const string& s) {
    istringstream istr{s};
    char c = 0;
    c = istr.get();
    if (c == '0') {
        c = istr.get();
        if (c == 'x') return M_base::hexadecimal;
        else return M_base::octal;
    }
    return M_base::decimal;
}