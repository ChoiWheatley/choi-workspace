/*
 * Chapter 7 : Refining and Completing a Calculator

 * Simple calculator 
 * This program implements a basic expression calculator
 * Input from cin and output from cout object
 * 
 * grammer {
 * Calculation:
 *      Statements
 *      Print
 *      Quit
 *      Expression
 * Statements:
 *      Declaration
 *      Assignment
 * Declaration:
 *      "let" Name '=' Expression
 *      "const" Name '=' Expression
 * Assignment:
 *      Name '=' Expression
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
 *      "sqrt" '(' Expression ')'
 *      "pow" '(' Expression ',' Expression ');
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
double statement();
double declare(char c);
double assignment(string s);
double expression();
double term();
double primary();
void show_token(Token, string);
void calculate();
double set_value(string, double);
bool is_declared(string s);
double define_var(string s, double d);
double define_const(string s, double d);
double find_value(string s);
bool is_constant(string s);
// Token get_token(); // depricated

// global variables

constexpr char T_num = 'n';
constexpr char T_quit = 'q';
constexpr char T_print = ';';
constexpr char T_assign = '=';
constexpr char T_let_token = 'L';
constexpr char T_const_token = 'C';
constexpr char T_name = 'a';
const string T_prompt = "> ";
const string T_result = "= ";
const string T_let_keyword = "let";
const string T_cosnt_keyword = "const";
const string T_quit_keyword = "quit";
const string T_exit_keyword = "exit";
//vector<Token> tok;


class Token{
public:
    char kind;
    double value;
    string name;
    Token(char k) : kind{k}, value{0} {}        // C++11 인가? 처음 보는 생성자의 구현모습이다...
    Token(char k, double v) : kind{k}, value{v} {}
    Token(double v) : kind{T_num}, value{v} {}
    Token(string s) : name{s}, value{0} {
        if (s == T_let_keyword) kind = T_let_token;
        else if (s == T_cosnt_keyword) kind = T_const_token;
        else if (s == T_quit_keyword ||
                s == T_exit_keyword
        ) kind = T_quit;
        else kind = T_name;
    }
    Token() : kind{0}, value{0}, name{""} {}
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
Token_Stream ts{};

// User can define variables 
// you can access variables by a glabal variable 'var_table'
class Variable{
public:
    string name;
    double value;
    inline bool is_constant() {return const_checkbox;}
    Variable() : name{}, value{0} {}
    Variable(string s, double v) : name{s}, value{v} {}
    Variable(string s, double v, char token) : name{s}, value{v} {
        if (token == T_const_token) const_checkbox = true;
        else if (token == T_let_token) const_checkbox = false;
        else error ("Unknown const token.");
    }
private:
    bool const_checkbox = false;
};
vector<Variable> var_table;
// deprecated 
class Constant {
public:
    string name;
    double value;
    Constant(string s, double v) : name{s}, value{v} {}
};
// deprecated 
vector<Constant> const_table;
class Symbol_table {
public:
    double get(string s);
    double set(string s, double d);
    double declare(char c);
    bool is_declared(string s);
    Variable find_var(string s);
private:
    vector<Variable> var_table;
};
Symbol_table st;




/* main function

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
        define_const("pi", 3.1415926535);
        define_const("e", 2.7182818284);
        calculate();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        cerr << "excpetion detected!\n";
        cout << "Please type 'q' to close the window\n";
        for (char exitCode; cin >> exitCode;)
            if (exitCode == T_quit)
                return 2;
    }
    return 0;
}
double statement()
{
    Token t = ts.get();
    if (t.kind == T_let_token ||
        t.kind == T_const_token)
        return st.declare(t.kind);
    if (t.kind == T_name) {
        Token t2 = ts.get();
        if (t2.kind == T_assign) return assignment(t.name);
        else ts.putback(t2);
    }
    ts.putback(t);
    return expression();
}
// find variable from ts.var_table and change it 
// to expression
double assignment(string s)
{
    // assume we already met T_assign keyword
    // pre-condition : if user wants to change value from constant, error
    if (st.find_var(s).is_constant()) error ("you cannot change constant. : ", s);
    return set_value(s, expression());
}
void calculate()
{
    while (cin) {
        try {
            cout << T_prompt;
            Token t = ts.get();
            while (t.kind == T_print)
                t = ts.get(); // eats ';', as T_quit
            if (t.kind == T_quit)
                return;
            ts.putback(t);
            cout << T_result << statement() << endl;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            cout << "Please type ';' to continue or 'q' to quit ";
            ts.ignore(T_print);
        }
        catch (...)
        {
            cerr << "excpetion detected!\n";
            cout << "Please type 'q' to close the window\n";
            for (char exitCode; cin >> exitCode;)
                if (exitCode == T_quit)
                    return;
        }
    }
}




/* ts as token stream 

████████ ███████ 
   ██    ██      
   ██    ███████ 
   ██         ██ 
   ██    ███████ 
                 

*/ 
//ts.size()를 먼저 보고 최근걸 꺼내주거나 cin에서 새로 꺼내오거나
// 해당 토큰을 사용하지 않으면 직접 집어넣어야 한다.
Token Token_Stream::get(){
    if (!stack.empty()) {
        Token ret = stack.back();
        stack.pop_back();
        return ret;
    }
    char tok_char = 0;
    cin >> tok_char;
    switch (tok_char) {
    case T_print:     // for print the result
    case T_quit:      // for print the result and exit
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
    case '=':
    case ',':
        return Token {tok_char};

    case '.': case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9': 
    {
        cin.putback(tok_char);
        double tok_num;
        cin >> tok_num;
        return Token {T_num, tok_num};
    }
    default:
        // name, 첫 글자는 알파벳, 나머지는 알파벳과 숫자, underscore만 사용
        if (isalpha(tok_char)) {
            string s;
            s += tok_char;
            while (cin.get(tok_char) &&
                   isalpha(tok_char) ||
                   isdigit(tok_char) ||
                   tok_char == '_')
                s += tok_char;
            cin.putback(tok_char);
            return Token{s};
        }
        error ("Invalid Token : '"+ to_string(tok_char)+ "'");
    }
    return Token{};
}
// ignore token stream until the parameter is found
void Token_Stream::ignore(char c)
{
    if (!stack.empty() && c == stack.back().kind) {
        return;
    }
    char ch = 0;
    while(cin >> ch)
        if (ch == c) return;
}

/* calc

 ██████  █████  ██       ██████ 
██      ██   ██ ██      ██      
██      ███████ ██      ██      
██      ██   ██ ██      ██      
 ██████ ██   ██ ███████  ██████ 
                                
                                
*/

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
            int int_left = static_cast<int> (left);
            int int_right = static_cast<int> (primary());
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
    case T_num:
        return t.value;
    case T_name:
    {
        if (t.name == "sqrt") {
            //sqrt(double arg);
            double ret = expression();
            if (ret < 0) error ("cannot be negative in sqrt()!");
            return sqrt(ret);
        }
        if (t.name == "pow") {
            //pow(double arg1, int arg2);
            // ','로 두 개의 인자를 받아들여야 한다. 
            // 인자의 개수가 모자란 경우 오류를 출력.
            try
            {
                double arg1 = expression();
                int arg2 = static_cast<int>(expression());
                return pow(arg1, arg2);
            }
            catch(const std::exception& e)
            {
                cout << e.what() << ' ';
                error("invalid arguments");
            }
            
        }
        return find_value(t.name);
    }
    case T_assign:
        return expression();
    case '(':
    {
        double d = expression();
        t = ts.get();
        if (t.kind == ',') {
            ts.putback(Token{'('});
            return d;
        }
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

/* symbol_table

███████ ██    ██ ███    ███ ██████   ██████  ██      
██       ██  ██  ████  ████ ██   ██ ██    ██ ██      
███████   ████   ██ ████ ██ ██████  ██    ██ ██      
     ██    ██    ██  ██  ██ ██   ██ ██    ██ ██      
███████    ██    ██      ██ ██████   ██████  ███████ 

*/
double Symbol_table::get(string s) { return find_var(s).value; }
double Symbol_table::set(string s, double d) { find_var(s).value = d; }
// declare variable from token stream input
double Symbol_table::declare(char tok)
{
    string newname;
    double newvalue;
    Token t = ts.get();
    if (t.kind != T_name) error ("name expected in declaration!");
    if (is_declared(t.name)) error ("given name already declared");
    newname = t.name;
    t = ts.get();
    if (t.kind != T_assign) error ("No '=' sign in declaration!");
    ts.putback(t);
    newvalue = expression();
    var_table.push_back(Variable{newname, newvalue, tok});
    return newvalue;
}
bool Symbol_table::is_declared(string s)
{
    for (auto i : var_table)
        if (i.name == s) return true;
    return false;
}
Variable Symbol_table::find_var(string s)
{
    for (int i = 0; i < var_table.size(); i++)
        if (var_table[i].name == s) return var_table[i];
    error ("no symbol found");
    return Variable{};
}


/* miscellaneous
███    ███ ██ ███████  ██████ ███████ ██      ██       █████  ███    ██ ███████  ██████  ██    ██ ███████ 
████  ████ ██ ██      ██      ██      ██      ██      ██   ██ ████   ██ ██      ██    ██ ██    ██ ██      
██ ████ ██ ██ ███████ ██      █████   ██      ██      ███████ ██ ██  ██ █████   ██    ██ ██    ██ ███████ 
██  ██  ██ ██      ██ ██      ██      ██      ██      ██   ██ ██  ██ ██ ██      ██    ██ ██    ██      ██ 
██      ██ ██ ███████  ██████ ███████ ███████ ███████ ██   ██ ██   ████ ███████  ██████   ██████  ███████ 
*/
void show_token(Token t, string caller = "")
{
    if (!caller.empty()) { cout << "DEBUG : in " << caller << ", "; }
    cout << "kind : '" << t.kind << "', value : '" << t.value << "', name : '" << t.name << "'\n";
}
bool is_number(string s)
{
    try { if (stod(s) != 0) return true; }
    catch(...) { return false; }
    return false;
}
bool is_declared(string s) 
{
    for (const Variable & i : var_table) {
        if (s == i.name) return true;
    }
    for (const Constant & i : const_table) {
        if (s == i.name) return true;
    }
    return false;
}
double define_var(string s, double d) 
{
    if (is_declared(s)) { error(s, " declared twice"); }
    var_table.push_back(Variable{s, d});
    return d;
}
double define_const(string s, double d)
{
    if (is_declared(s)) { error(s, " declared twice"); }
    const_table.push_back(Constant{s, d});
    return d;
}
bool is_constant(string s)
{
    for (auto i : const_table) 
        if (i.name == s) return true;
    return false;
}
/* deprecated
██████  ███████ ██████  ██████  ██  ██████  █████  ████████ ███████ ██████  
██   ██ ██      ██   ██ ██   ██ ██ ██      ██   ██    ██    ██      ██   ██ 
██   ██ █████   ██████  ██████  ██ ██      ███████    ██    █████   ██   ██ 
██   ██ ██      ██      ██   ██ ██ ██      ██   ██    ██    ██      ██   ██ 
██████  ███████ ██      ██   ██ ██  ██████ ██   ██    ██    ███████ ██████  

*/
// <IMPORTANT> Might deprecated because of Symbol_table

// assume Token_Stream::get() already ate "let" keyword
// get name from token stream and find out if '=' is exist
double declare(char c)
{
    string ret_str;
    double ret_d;
    Token t = ts.get();
    if (t.kind != T_name) error ("name expected in declaration!");
    ret_str = t.name;
    t = ts.get();
    if (t.kind != T_assign) error ("No '=' sign in declaration!, ", ret_str);
    ts.putback(t);
    ret_d = expression();
    switch (c) {
    case T_let_token:
        return define_var(ret_str, ret_d);
    case T_const_token:
        return define_const(ret_str, ret_d);
    default:
        error ("unknown error in declaration");
    }
    return 0;
}
double find_value(string s)
{
    for (auto i : var_table)
        if (i.name == s) return i.value;
    for (auto i : const_table)
        if (i.name == s) return i.value;
    error ("no variable / constant found.\n");
    return 0;
}
// set variable from var_table 
double set_value(string s, double d)
{
    // pre condition : if there is already a given name,
    // reallocate with new value
    for (int i = 0; i < var_table.size(); i++) {
        if (var_table[i].name == s) var_table[i].value = d;
    }
    var_table.push_back(Variable(s, d));    
    return d;
}
double find_value(string s)
{
    for (auto i : var_table)
        if (i.name == s) return i.value;
    for (auto i : const_table)
        if (i.name == s) return i.value;
    error ("no variable / constant found.\n");
    return 0;
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
            ret = Token{T_num, stod(num_chunk)};
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