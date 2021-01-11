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
 * << second attempt 2021. 1. 11 >>>
 * 1. M_input struct revision : int value and M_base base :: input time decision
 * 2. It would be ease to print out from M_input
 * 
 * <<< first attempt 2021. 1. 10 >>>
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
struct M_input {
    vector<int> value;
    vector<M_base> base;
};
const string octal_format = "01234567";
const string hexadec_format = "0123456789abcdefABCDEF";
constexpr char Cmd_exit = '|';

M_input prompt();
M_input input(istream&);
ostream& operator<<(ostream& os, const M_input& m);
int longest_int(const vector<int>&);
M_base base(const string&);
//istream& operator>>(istream& is, string& str);
bool is_whitespace(char c);
bool is_octal(char c);
bool is_hexadec(char c);
void to_ios_base(ostream&, M_base);
int string_to_int(const string&);

int main(void) 
{
    try{
        // cout << prompt() << '\n';
        cout << input(* make_unique<ifstream>("sample_input.txt")) << '\n';
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
    return M_input{input(cin)};
}
// try to find out whether a word is correct format for dec, oct, hex
M_input input(istream& is) {
    M_input ret;
    for (char c; true; ) {
        c = is.get();
        // is error handling
        if (is.good() && c == Cmd_exit) break;
        else if (is.eof()) { // assume eof() is also a exit command 
            break;
        } 
        else if (is.fail()) throw ERRCODE::fail;
        else if (is.bad()) throw ERRCODE::bad;

        is.unget();
        string newnum;
        is >> newnum;
        // is error handling
        if (is.eof()) break;
        else if (is.fail()) { // skip to next number
            is.clear();
            continue;
        }
        else if (is.bad()) throw ERRCODE::bad;

        // newnum format checking and newnum error handling
        if (base(newnum) == M_base::error) continue;    //skip to next number
        if (ret.base.size() != ret.value.size()) error ("fatal error : base and value index mismatch");
        ret.base.push_back(base(newnum));
        ret.value.push_back(string_to_int(newnum));
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
    int longest_value = 0;
    longest_value = longest_int(m.value);
    for (int i = 0; i < m.value.size(); i++) {
        to_ios_base(os, m.base[i]);
        os.setf(ios_base::showbase);
        os << setw(longest_value + 3) << right <<  m.value[i] << ' ' << 
                setw(string("hexadecimal").size() + 3) << left << m_base[static_cast<int>(m.base[i])] << ' ' <<
                "converts to\t" << 
                setw(longest_value + 3) << right << noshowbase << dec << m.value[i] << ' ' << 
                "decimal\n";
    }
    return os;
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
int longest_int(const vector<int>& v) {
    int ret = 0;
    for (auto i : v) {
        if (ret < to_string(i).size()) ret = to_string(i).size();
    }
    return ret;
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
void to_ios_base(ostream& os, M_base m) {
    switch(m) {
        case M_base::decimal:
            os.setf(ios_base::dec, ios_base::basefield);
            break;
        case M_base::octal:
            os.setf(ios_base::oct, ios_base::basefield);
            break;
        case M_base::hexadecimal:
            os.setf(ios_base::hex, ios_base::basefield);
            break;
        default:
            error("serious problem occured converting M_base into ios_base");
    }
}
int string_to_int(const string& str) {
    istringstream istr{str};
    istr.unsetf(ios_base::dec | ios_base::oct | ios_base::hex);
    int ret;
    istr >> ret;
    return ret; 
}