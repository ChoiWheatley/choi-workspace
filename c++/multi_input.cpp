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
    hexadecimal,
    error
};
const vector<string> m_base {
    "octal",
    "decimal",
    "hexadecimal"
};
const vector<char> whitespace {
    ' ',
    '\t',
    '\n'
};
const string octal_format = "01234567";
const string hexadec_format = "0123456789abcdefABCDEF";

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
istream& operator>>(istream& is, string& str);
bool is_whitespace(char c);
bool is_octal(char c);
bool is_hexadec(char c);

int main(void) 
{
    try{
        // cout << prompt() << '\n';
        vector<string> original = input(* make_unique<ifstream>("sample_input.txt"));
        vector<int> converted = output(original);
        cout << M_input{original, converted};
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
        else if (is.fail()) {
            is.clear();
            continue;               // skip to next string
        }
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
// we have to find out octal, decimal, and hexa forms
// octal : 0 ~ 7
// decimal : digit 
// hexa : digit || 'a' ~ 'f' || 'A' ~ 'F'
M_base base(const string& s) {
    istringstream istr{s};
    M_base base_flag = M_base::error;
    char c = 0;
    c = istr.get();
    // first one or two characters to find out suffix
    if (c == '0') {
        c = istr.get();
        if (c == 'x') base_flag = M_base::hexadecimal;
        else {
            base_flag = M_base::octal;
            istr.putback(c);
        }
    } else if (isdigit(c)){
        base_flag = M_base::decimal;
        istr.putback(c);
    } else return M_base::error;

    // based on suffix, we have to find out other characters 
    // satisfying own format
    for (c = 0; istr && base_flag != M_base::error; ) {
        c = istr.get();
        if (istr.eof()) break;
        switch (base_flag)
        {
        case M_base::decimal:
            if (!isdigit(c))
                base_flag = M_base::error;
            break;
        case M_base::octal:
            if (!is_octal(c))
                base_flag = M_base::error;
            break;
        case M_base::hexadecimal:
            if (!is_hexadec(c))
                base_flag = M_base::error;
            break;
        }
    }
    return base_flag;
}
// we use 'base' function to do a format checking
istream& operator>>(istream& is, string& str) {
    // override : only read digit and 'x' character
    // when other character was found, turn istream to failbit
    for (char c; true; ) {
        c = is.get();
        if (is.fail()) return is;
        if (is.bad()) return is;

        // loop break point handling
        if (is_whitespace(c)) break;
        str.push_back(c);
    }
    // base format checking
    switch(base(str)) {
        case M_base::decimal:
        case M_base::octal:
        case M_base::hexadecimal:
            break;
        case M_base::error:
            is.clear(ios_base::failbit);
            break;
    }
    return is;
}
bool is_whitespace(char c) {
    for (auto i : whitespace) {
        if (c == i) return true;
    }
    return false;
}
bool is_octal(char c) {
    for (char i : octal_format) {
        if (c == i) return true;
    }
    return false;
}
bool is_hexadec(char c) {
    for (char i : hexadec_format) {
        if (c == i) return true;
    }
    return false;
}