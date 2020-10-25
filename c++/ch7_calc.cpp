/*
 * Chapter 7 : Refining and Completing a Calculator

 * Simple calculator 
 * This program implements a basic expression calculator
 * Input from cin and output from cout object
 * 
 * grammer {
 * Statements:
 *      Expression
 *      Print
 *      Quit
 * Print:
 *      ;
 * Quit:
 *      q
 * Expression:
 *      Term
 *      Expression '+' Term
 *      Expression '-' Term
 * Term:
 *      Primary
 *      Expression '*' Primary
 *      Expression '/' Primary
 *      Expression '%' Primary
 * Primary:
 *      Number
 *      '(' Expression ')'
 *      '+' Primary
 *      '-' Primary
 * Number:
 *      a floating point literals
 *} 

Input comes from cin through the Token_Stream 
as ts


 */

#include "std_lib_facilities.h"
#include <unistd.h> // to use sleep() function

// pre defined

// function to read a token from cin object
class Token;
class Token_Stream;
double expression();
double term();
double primary();
void show_token(Token, string);
void calculate();
// Token get_token(); // depricated

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
    Token get();        // ts.size()를 먼저 보고 최근걸 꺼내주거나 cin에서 새로 꺼내오거나
                        // 해당 토큰을 사용하지 않으면 직접 집어넣어야 한다.
    void putback(Token t){ stack.push_back(t); }        // put a token back
    void ignore(char c);                                // discard charactor up to and including an argument
    Token_Stream(char k) : stack{Token{k}} {}
    Token_Stream(char k, double v) : stack{Token{k,v}} {}
    Token_Stream() : stack{} {}
private:
    vector<Token> stack;
};
// User can define variables 
// you can access variables by a glabal variable 'var_table'
class Variable{
public:
    string name;
    double value;
    Variable(string s, double v) : name{s}, value{v} {}
};

// global variables

Token_Stream ts{};
vector<Variable> var_table;
constexpr char T_Num = 'n';
constexpr char T_Quit = 'q';
constexpr char T_Print = ';';
const string T_Prompt = "> ";
const string T_Result = "= ";
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
    calculate();
    return 0;
}
//
//

void calculate()
{
    while (cin) {
        try
        {
            cout << T_Prompt;
            Token t = ts.get();
            while (t.kind == T_Print)
                t = ts.get(); // eats ';'
            if (t.kind == T_Quit)
                return;
            ts.putback(t);
            cout << T_Result << expression() << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << " ";
            cout << "Please type ';' to continue or 'q' to quit\n";
            ts.ignore(';');
        }
        catch (...)
        {
            cerr << "excpetion detected!\n";
            cout << "Please type 'q' to close the window\n";
            for (char exitCode; cin >> exitCode;)
                if (exitCode == T_Quit)
                    return;
        }
    }
}

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
    char tok_char = 0;
    cin >> tok_char;
    switch (tok_char) {
    case T_Print:     // for print the result
    case T_Quit:      // for print the result and exit

    case '+': 
    case '-': 
    case '*': 
    case '/': 
    case '%': 
    case '!': 
    case '(': 
    case ')': 
    case '{': 
    case '}':
        return Token {tok_char};

    case '.': case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': 
    {
        cin.putback(tok_char);
        double tok_num;
        cin >> tok_num;
        return Token {T_Num, tok_num};
    }
    default:
        error ("Invalid Token");
    }
    return Token{0};
}
void Token_Stream::ignore(char c)
{
    if (!stack.empty() && c == stack.back().kind) {
        return;
    }
    char ch = 0;
    while(cin >> ch)
        if (ch == c) return;
}
void Variable::set_value(string s, double v)
{
    
}
double Variable::get_value (string s)
{

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
        case '%':
        {
            int int_left = narrow_cast<int> (left);
            int int_right = narrow_cast<int> (primary());
            if (int_right == 0) error("Cannot divided by zero!\n");
            left = int_left % int_right;
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
    case '{':
    {
        double d = expression();
        t = ts.get();
        if (t.kind != '}') error ("<><><> '}' expected! <><><>\n");
        return d;
    }
    case '-':       // unary minus
        return (-1) * primary();
    case '+':       // unary plus
        return primary();
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
bool is_number(string s)
{
    try { if (stod(s) != 0) return true; }
    catch(...) { return false; }
    return false;
}











//DEPRICATED!
/*
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
*/