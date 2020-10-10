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

vector<Token> tok;
constexpr char T_Num = 'n';

// function to read a token from cin object
Token get_token();
void show_tok();
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
        Token t = get_token();
        tok.push_back(t);
    }
    show_tok();
	return 0;
}
//
//

Token get_token()
{
    char tok_char;
    double tok_num; 
    Token ret {T_Num, 0.0};
    if (cin >> tok_num) {
        ret.kind = T_Num;
        ret.value = tok_num;
    } else if (cin >> tok_char) {
        ret.kind = tok_char;
    } else { throw runtime_error("invalid input\n"); }
    return ret;
}

void show_tok()
{
    for (auto i : tok)
        cout << i.kind << " ";
    cout << endl;
    for (auto i : tok)
        cout << i.value << " ";
    cout << endl;
}