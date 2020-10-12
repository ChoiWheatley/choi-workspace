/*
 * Using Tokens, we can simply implement the order of 
 * operators, parentheses, and number
 * we need three kinds of tokens :
 * 1. Floating point literals such as 3.14, 0.27e2, 42
 * 2. operators such as '+', '-', '*', '/'
 * 3. parentheses such as '(', ')'
 */

#include "std_lib_facilities.h"
#include <unistd.h>

class Token{
public:
    char kind;
    double value;
    Token(char k) : kind{k}, value{0} {}        // C++11 인가? 처음 보는 생성자의 구현모습이다...
    Token(char k, double v) : kind{k}, value{v} {}
};

const vector<char> operands {
    '+', '-', '*', '/', '%', '(', ')'
};

vector<Token> tok;
constexpr char T_Num = 'n';

// function to read a token from cin object
inline Token get_token();
void show_tok();
bool is_operand(char);
bool is_number(char);
/*

███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 

*/
int main()
{
    while (cin)
    {
        tok.push_back(get_token());
        show_tok();
    }
    show_tok();
    return 0;
}
//
//

bool is_number(char c)
{
    if (c >= 48 && c <= 57) return true;
    return false;
}
bool is_operand(char c)
{
    for (auto i : operands)
        if (c == i) return true;
    return false;
}
inline Token get_token()
{
    double tok_num = 0;
    char tok_char;
    static char prev_tok;
    string num_chunk = "";
    Token ret {'x', 0.0};
    
    if (is_operand(prev_tok)) { ret = Token {prev_tok}; }
    else {
        cin >> tok_char;
        //if (tok_char == cin.eof()) return ret;
        //if (tok_char == '\n') cin.clear();
        for ( ; !is_operand(tok_char); tok_char = cin.get() )
            num_chunk.push_back(tok_char);
        cout << "num_chunk : " << num_chunk << endl;
        ret = Token {T_Num, stod(num_chunk)};
    }
    prev_tok = tok_char;
    return ret;
}

void show_tok()
{
    for (auto i : tok)
        cout << i.kind << " = " << i.value << endl;
    cout << endl;
}