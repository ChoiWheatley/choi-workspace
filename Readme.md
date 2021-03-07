# choe-workspace/Readme.md

# ./C++

## 개요

Study C++ Programming Language using the book 'Programming: Principles and Practice Using C++' (PPPUC++) created by Bjarne Stroustroup. Focused on how to implement some useful ideas using c++'s technics. This book is not an reference book.

## TODO

- [ ]  in Ch12 Ellipse Implementation, Text alignment method needed! using bitmask
    - [ ]  I found out there already be `Fl_Widget::align()` method.
- [ ]  in Ch12, I need to develop my own base class `Shape` which includes `{Circle, Rectangle, Axis, Polyline, ...}`
- [ ]  in Ch12 Offscreen Drawing and Event handling
- [ ]  in Ch11 streambuffer → making custom stream class

## TIPS

- Compile option :

```makefile
CXXFLAGS = $(shell fltk-config --use-gl --use-images --cxxflags) -I. -std=c++17 -Wall
LDFLAGS = $(shell fltk-config --use-gl --use-images --ldflags)
```

- Function pointer or typedef function

```cpp
typedef typename functionname (typename);
typename (*functionname)(typename);
[...]
void some_callback_function(functionname, [...]);
```

- When you decided to draw your own Widget, every drawing functionalities are kept inside the `draw()` function.

## ??? (Unsolved Questions)

- I couln't find out how to use `fl_translate(), fl_transform(), [...]` functions
-

---

# ./ALGORITHMS

## 개요

도서 '프로그래밍 대회에서 배우는 알고리즘 문제해결전략' (프알문, APSS) 로 공부를 시작했고, 최근에 21년 2월 10일부터 3월 말까지(45일) 백준 인강을 구독했기에 해당 문제들 위주로 정리해서 올릴 예정이다.

## TODO

## TIP
- passing const reference array into parameter : "const type (&name)[][]"
- You can use Compile-time table using constexpr array function (I dunno well...)  http://cplusplus.com/forum/beginner/249023/ 
	Compile time initialization   // https://en.cppreference.com/w/cpp/language/constexpr
- 어떤 수 i 에 대하여 1~M 까지 반복한다면 `((i-1) % M)+1` 이런 식으로 인덱스를 짜면 좋다. (아니 이렇게 해야 한다)
- 2차원 벡터 초기화 : `vector<vector<int>> board(n, vector<int>(m, 0)); `
- `ios_base::setw()` 는 `<iomanip>` header 파일에 들어있다.
- To make cin, cout faster,
```cpp
ios_base::sync_with_studio(false);
cin.tie(nullptr);
cout.tie(nullptr);
```
- Backtracking = Bruteforce + Condition
	We can improve Bruteforce program using backtracking method. Halting the iteration in which the result can be impossible or tedious. 


---

# ./HTML

## 개요

## TODO

