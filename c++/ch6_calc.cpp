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
    Token() : kind{'x'}, value{0} {}
};

Token get_token();
void show_token(Token, string);

// as Token Stream
class Token_Stream{
public:
    Token get(){// ts.size()를 먼저 보고 최근걸 꺼내주거나 cin에서 새로 꺼내오거나
                // 해당 토큰을 사용하지 않으면 직접 집어넣어야 한다.
        if (stack.empty()) return get_token();
        Token ret = stack.back();
        stack.pop_back();
        return ret;
    } 
    void push(Token t){ 
        //show_token(t, "TS");
        stack.push_back(t); } 
    Token_Stream(char k) : stack{Token{k}} {}
    Token_Stream(char k, double v) : stack{Token{k,v}} {}
    Token_Stream() : stack{} {}
private:
    vector<Token> stack;
};

// function to read a token from cin object
bool is_operand(char);
double expression();
double term();
double primary();

const vector<char> operands {
    '+', '-', '*', '/', '%', '(', ')'
};

vector<Token> tok;
Token_Stream ts{};
constexpr char T_Num = 'n';


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
        while (cin)
        {
            cout << " = ";
            cout << expression() << endl;
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
            ts.push(t);
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
            ts.push(t);
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