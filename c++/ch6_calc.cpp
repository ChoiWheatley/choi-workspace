/*
 * Using Tokens, we can simply implement the order of 
 * operators, parentheses, and number
 * we need three kinds of tokens :
 * 1. Floating point literals such as 3.14, 0.27e2, 42
 * 2. operators such as '+', '-', '*', '/'
 * 3. parentheses such as '(', ')'
 */

#include "std_lib_facilities.h"
#include <unistd.h> // to use sleep() function

// pre defined

// function to read a token from cin object
class Token;
class Token_Stream;
bool is_operand(char);
bool is_number(string);
double expression();
double term();
double primary();
void show_token(Token, string);
Token get_token(); // depricated

class Token{
public:
    char kind;
    double value;
    Token(char k) : kind{k}, value{0} {}        // C++11 인가? 처음 보는 생성자의 구현모습이다...
    Token(char k, double v) : kind{k}, value{v} {}
    Token() : kind{0}, value{0} {}
};
// as Token Stream
class Token_Stream{
public:
    Token get();// ts.size()를 먼저 보고 최근걸 꺼내주거나 cin에서 새로 꺼내오거나
                // 해당 토큰을 사용하지 않으면 직접 집어넣어야 한다.
    void putback(Token t){ stack.push_back(t); } 
    Token_Stream(char k) : stack{Token{k}} {}
    Token_Stream(char k, double v) : stack{Token{k,v}} {}
    Token_Stream() : stack{} {}
private:
    vector<Token> stack;
};
const vector<char> operands {
    '+', '-', '*', '/', '%', '(', ')'
};

// global variables

Token_Stream ts{};
constexpr char T_Num = 'n';
//vector<Token> tok;



/*

███    ███  █████  ██ ███    ██ 
████  ████ ██   ██ ██ ████   ██ 
██ ████ ██ ███████ ██ ██ ██  ██ 
██  ██  ██ ██   ██ ██ ██  ██ ██ 
██      ██ ██   ██ ██ ██   ████ 

*/
int main()
{
    try
    {
        double val = 0;
        while (cin)
        {
            Token t = ts.get();
            if (t.kind == 'q') break;
            if (t.kind == ';') 
                cout << " = " << val << endl;
            else 
                ts.putback(t);
            val = expression();
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "excpetion detected!\n";
        return 2;
    }
    
    return 0;
}
//
//


Token Token_Stream::get(){// ts.size()를 먼저 보고 최근걸 꺼내주거나 cin에서 새로 꺼내오거나
                          // 해당 토큰을 사용하지 않으면 직접 집어넣어야 한다.
/*
 * ㅁ 음수인 경우 (-1) 문제를 해결하지 못하는 버그 발생.
 * ㅁ pppuc++ 교재에서는 cin.putback() 함수를 활용하여 숫자를 입력받으려고 하고 있다.
 */
    if (!stack.empty()) {
        Token ret = stack.back();
        stack.pop_back();
        return ret;
    }
    try {
        double tok_num = 0;
        char tok_char = 0;
        string num_chunk = "";
        tok_char = cin.get();
        if (is_operand(tok_char)) {
            return Token{tok_char};
        } else {
            for (; !is_operand(tok_char); tok_char = cin.get()) 
                num_chunk.push_back(tok_char);
            if (is_number(num_chunk)) return Token {'n', stod(num_chunk)};
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return Token{0};
}


double expression()
{
    double left = term();
    Token t = ts.get();
    //show_token(t, "Expression");
    for (; ; t = ts.get()) {
        switch (t.kind) {
        case '+':
            left += term();
            break;
        case '-':
            left -= term();
            break;
        default:
            ts.putback(t);
            return left;
        }
    }
    return left;
}

double term()
{
    double left = primary();
    Token t = ts.get();
    //show_token(t, "Term");
    for (; ; t = ts.get())
    {
        switch (t.kind)
        {
        case '*':
            left *= primary();
            break;
        case '/':
        {
            double d = primary();
            if (d == 0) { error("divided by zero!\n"); }
            left /= d;
            break;
        }
        default:
            ts.putback(t);
            return left;
        }
    }
    return left;
}
double primary()
{
    Token t = ts.get();
    //show_token(t, "Primary");
    switch (t.kind)
    {
    case 'n':
        return t.value;
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != ')') error ("<><><> ')' expected! <><><>\n");
        return d;
    }
    default:
        error ("<><><> Primary Expected!!!!!! <><><>\n");
    }
    return 0;
}


/*
 *
 * 
 * 
 * 
 */

void show_token(Token t, string caller = "")
{
    if (!caller.empty()) { cout << "DEBUG : in " << caller << ", "; }
    cout << "SHOW_TOKEN()\n";
    cout << "'" << t.kind << "' = " << t.value << endl;
}
bool is_operand(char c)
{
    for (auto i : operands)
        if (c == i) return true;
    return false;
}
bool is_number(string s)
{
    try { if (stod(s) != 0) return true; }
    catch(...) { return false; }
    return false;
}











//DEPRICATED!
Token get_token()
{
    double tok_num = 0;
    char tok_char;
    static char prev_tok;
    string num_chunk = "";
    Token ret {'x', 0.0};

    try
    {
        if (is_operand(prev_tok)){
            ret = Token{prev_tok};
        }
        else{
            cin >> tok_char;
            if (is_operand(tok_char))    return Token{tok_char};
            for (; !is_operand(tok_char) && tok_char != '\n'; tok_char = cin.get())
                num_chunk.push_back(tok_char);
            ret = Token{T_Num, stod(num_chunk)};
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    prev_tok = tok_char;
    return ret;
}