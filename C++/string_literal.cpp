#include <iostream>
using namespace std;

int main() {
    char newline = '\n';
    char tab = '\t';
    char backspace = '\b';
    char backslash = '\\';
    char nullChar = '\0';

    cout << "Newline character: " << newline << "ending" << endl;
    cout << "Tab character: " << tab << "ending" << endl;
    cout << "Backspace character: " << backspace << "ending" << endl;
    cout << "Backslash character: " << backslash << "ending" << endl;
    cout << "Null character: " << nullChar << "ending" << endl;

    ////////////////////////////////////////////////////////////////////////////
    /*
    char c1 = '\100';
    char c2 = '\1000'; //octal characters treated as a 3-digit octal sequence, 
    char c3 = '\009';
    char c4 = '\089';
    char c5 = '\qrs';
    
    cout << c1 << endl; //'@'
    cout << c2 << endl; //컴파일 과정에서 WARNING '0'
    cout << c3 << endl; //컴파일 과정에서 WARNING '9'
    cout << c4 << endl; //컴파일 과정에서 WARNING '9'
    cout << c5 << endl; //컴파일 과정에서 WARNING 's'
    */

    ////////////////////////////////////////////////////////////////////////////
    const char *narrow_string_literal = "abcd";
    const char *narrow_string_literal2 = "아스키는2바이트에 들어가서 narrow, 유니코드는 4바이트에 들어가서 wide";
    const wchar_t *wide_string_literal = L"아스키는2바이트에 들어가서 narrow, 유니코드는 4바이트에 들어가서 wide";
    
    cout << narrow_string_literal << endl;
    cout << narrow_string_literal2 << endl; //왜 이놈이 되는거지?
    wcout << wide_string_literal << endl;   //왜 이놈은 안되는거지?

    ////////////////////////////////////////////////////////////////////////////
    const char* raw_narrow = R"(An unescaped \ character 안녕!)";
    const wchar_t* raw_wide = LR"(An unescaped \ character 안녕!)";
    const char* raw_utf8 = u8R"(An unescaped \ character 안녕!)";
    const char16_t* raw_utf16 = uR"(An unescaped \ character 안녕!)";
    const char32_t* raw_utf32 = UR"(An unescaped \ character 안녕!)";
    const wchar_t* wide_newline = LR"(
    Hello!
    and good bye
    and byebyebye
    )";

    cout << raw_narrow << endl;
    wcout << raw_wide << endl;
    cout << raw_utf8 << endl;
    wcout << raw_utf16 << endl;
    wcout << raw_utf32 << endl;
    wcout << wide_newline << endl;
}