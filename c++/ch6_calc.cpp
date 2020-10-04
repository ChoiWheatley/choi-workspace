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
void get_token(vector<Token> & tok);
void show_token(const vector<Token> & tok);
int find_next_operator(const string & str, int start);
bool is_operator(char c);
Token next_token(const string & str, int & start);

/*

███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 

*/
int main()
{
	// 클래스의 신기한 생성자로 새 변수를 초기화 하는 방법
    Token a1 {'+'};
    Token a2 {'0', 3.14e+2};
    Token a3 {a1};
    // Token a4;        // Token 클래스의 기본 생성자를 표기하지 않아 오류를 발생시킨다.

    get_token(tok);
    show_token(tok);

	return 0;
}
//
//

void get_token(vector<Token> & tok)
{
    string line;
    getline(cin, line, '\n');
    for (int i = 0; i < line.size(); i++)
    {
        if (is_operator(line[i]))
            tok.push_back(Token {line[i]});
        else
        {
            tok.push_back(next_token(line, i));
            i = find_next_operator(line, i) - 1;
        }
    }
}
void show_token(const vector<Token> & tok)
{
    for (auto i : tok)
        cout << "(" << i.kind << ") ";
    cout << endl;
    for (auto i : tok)
        cout << "(" << i.value << ") ";
    cout << endl;
}
int find_next_operator(const string & str, int start)
{
    for (int i = start; i < str.size(); i++)
        if (is_operator(str[i])) return i;
    return str.size();
}
bool is_operator(char c)
{
    switch (c)
    {
        case '+': case '-': case '*': case '/': //case '(': case ')':
            return true;
        default:
            return false;
    }
}
Token next_token(const string & str, int & start)
{
    int next = find_next_operator(str, start) - start;
    return Token {T_Num, stod(str.substr(start, next))};
}