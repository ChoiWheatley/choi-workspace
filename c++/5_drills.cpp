/*
 * <<<<< you may have guessed what the error is >>>>>
 * 
 * 1. Cout << "Success!\n"; 
 * 2. cout << "Success!\n; 
 * 3. cout << "Success" << !\n" 
 * 4. cout << success << '\n'; 
 * 5. string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n"; 
 * 6. vector<int> v(10); v(5) = 7; if (v(5)!=7) cout << "Success!\n"; 
 * 7. if (cond) cout << "Success!\n"; else cout << "Fail!\n"; 
 * 8. bool c = false; if (c) cout << "Success!\n"; else cout << "Fail!\n"; 
 * 9. string s = "ape"; boo c = "fool"<s; if (c) cout << "Success!\n"; 
 * 10. string s = "ape"; if (s=="fool") cout << "Success!\n"; 
 * 11. string s = "ape"; if (s=="fool") cout < "Success!\n"; 
 * 12. string s = "ape"; if (s+"fool") cout < "Success!\n"; 
 * 13. vector<char> v(5); for (int i=0; 0<v.size(); ++i) ; cout << "Success!\n"; 
 * 14. vector<char> v(5); for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; 
 * 15. string s = "Success!\n"; for (int i=0; i<6; ++i) cout << s[i]; 
 * 16. if (true) then cout << "Success!\n"; else cout << "Fail!\n"; 
 * 17. int x = 2000; char c = x; if (c==2000) cout << "Success!\n"; 
 * 18. string s = "Success!\n"; for (int i=0; i<10; ++i) cout << s[i]; 
 * 19. vector v(5); for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; 
 * 20. int i=0; int j = 9; while (i<10) ++j; if (j<i) cout << "Success!\n"; 
 * 21. int x = 2; double d = 5/(x–2); if (d==2*x+0.5) cout << "Success!\n"; 
 * 22. string<char> s = "Success!\n"; for (int i=0; i<=10; ++i) cout << s[i]; 
 * 23. int i=0; while (i<10) ++j; if (j<i) cout << "Success!\n"; 
 * 24. int x = 4; double d = 5/(x–2); if (d=2*x+0.5) cout << "Success!\n"; 
 * 25. cin << "Success!\n";
 */ 


#include "std_lib_facilities.h"

int main(void)
{
       try 
       {
           //

           cin << "Success!\n";

           //
           return 0;
       }
       catch (exception & e)
       {
           cerr << "error : " << e.what() << '\n';
           return 1;
       }
       catch (...)
       {
           cerr << "Ooooops.. unknown exception! \n";
           return 2;
       }
}

/*
 * 1. Cout << "Success!\n"; 
 * --- 'Cout' was not declared in this scope.
 * 
 * 2. cout << "Success!\n; 
 * --- missing terminating character
 * 
 * 3. cout << "Success" << !\n" 
 * --- stray '\' in program
 * 
 * 4. cout << success << '\n'; 
 * --- 'success' was not declared in this scope
 * 
 * 5. string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n"; 
 * --- conversion from 'int' to non-scalar type 'std::__cxx11::string' requested
 * --- cannot convert 'std::cxx11string' to 'int' in assignment
 * 
 * 6. vector<int> v(10); v(5) = 7; if (v(5)!=7) cout << "Success!\n"; 
 * --- no match for call to '(Vector<int>) (int)' =====> vector<int>를 리턴하고 int를 인자로 받는 "함수"로 간주하고 있다.
 * 
 * 7. if (cond) cout << "Success!\n"; else cout << "Fail!\n"; 
 --- 'cond' was not declared in this scope.
 *
 * 8. bool c = false; if (c) cout << "Success!\n"; else cout << "Fail!\n"; 
 * --- no error
 * 
 * 9. string s = "ape"; boo c = "fool"<s; if (c) cout << "Success!\n"; 
 * --- 'boo' was not declared in this scope
 * --- 'c' was not declared in this scope
 * 
 * 10. string s = "ape"; if (s=="fool") cout << "Success!\n"; 
 * --- no error
 * 
 * 11. string s = "ape"; if (s=="fool") cout < "Success!\n"; 
 * --- no match for 'operator<' comparison between object 'std::ostream' and 'const char [10]'
 * 
 * 12. string s = "ape"; if (s+"fool") cout < "Success!\n"; 
 * --- no match for 'operator<' comparison between object 'std::ostream' and 'const char [10]'
 * --- could not convert 'operator+' from 'std::string' to 'bool'
 * 
 * 13. vector<char> v(5); for (int i=0; 0<v.size(); ++i) ; cout << "Success!\n"; 
 * --- infinite loop
 * 
 * 14. vector<char> v(5); for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; 
 * --- no error 
 * 
 * 15. string s = "Success!\n"; for (int i=0; i<6; ++i) cout << s[i]; 
 * --- no compile error but when you run it, you will get a wrong answe
 * 
 * 16. if (true) then cout << "Success!\n"; else cout << "Fail!\n"; 
 * --- 'then' was not declared in this scope.
 * 
 * 17. int x = 2000; char c = x; if (c==2000) cout << "Success!\n"; 
 * --- no compile error, but narrow error occured (info loss)
 * --- 신기하다. narrow_conversion<T>를 사용하면 런타임에 exception이 throw되고,
 * --- (T){} 구문으로 type conversion 수행하면 compile time에 오류가 난다.
 * 
 * 18. string s = "Success!\n"; for (int i=0; i<10; ++i) cout << s[i]; 
 * --- 왜 아무 문제가 없는거지?
 * 
 * 19. vector v(5); for (int i=0; i<=v.size(); ++i) ; cout << "Success!\n"; 
 * --- Missing template arguments before 'v' --- 와 이걸 놓쳤네
 * 
 * 20. int i=0; int j = 9; while (i<10) ++j; if (j<i) cout << "Success!\n"; 
 * --- infinite loop
 * 
 * 21. int x = 2; double d = 5/(x–2); if (d==2*x+0.5) cout << "Success!\n"; 
 * --- floating point exception
 * 
 * 22. string<char> s = "Success!\n"; for (int i=0; i<=10; ++i) cout << s[i]; 
 * --- sting is not a template
 * 
 * 23. int i=0; while (i<10) ++j; if (j<i) cout << "Success!\n"; 
 * --- infinite loop, 'j' was not declared in this scope
 * 
 * 24. int x = 4; double d = 5/(x–2); if (d=2*x+0.5) cout << "Success!\n"; 
 * --- 문제없이 실행이 되잖아????
 * 
 * 25. cin << "Success!\n";
 * --- no match for 'operator<<' and 'const char[10]
 * 
 */ 