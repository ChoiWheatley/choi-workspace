# choi-workspace/Readme.md

# 리눅스IPC프로그래밍 :: inflearn.com
https://www.inflearn.com/course/%EB%A6%AC%EB%88%85%EC%8A%A4ipc%ED%94%84%EB%A1%9C%EA%B7%B8%EB%9E%98%EB%B0%8D
총 29개 수업˙총 11시간 27분

**중급자**를 위해 준비한**[웹 개발, 서버 개발] 강의입니다.**

**IPC 도구를 이용한 프로그래밍에서 더 나아가 "소프트웨어 요구사항에 맞는 IPC 도구를 적절히 선택해 설계/구현 할 수 있는 능력을 키우는 것"이 이 강좌의 최종 목표 입니다.**
### 이 강의를 듣고나면 당신은...

- Linux IPC 도구의 종류와 특징에 대해 알 수 있다.
    - POSIX & SYSV 프로그래밍 인터페이스 간에 비교 및 분석
        - IPC 도구 별 프로그래밍 및 실습
    - 소프트웨어 요구사항에 적합한 IPC 도구를 선택, 설계, 구현 할 수 있다.
    - 경쟁력 있는 리눅스 시스템 개발자.
        - 리눅스 커널, 디바이스 드라이버 등 도메인 specific 한 개발자로의 진화

# welcome, python!

## 개요

2021년 계절학기 "컴퓨팅적 사고" 수업을 듣기 위해 새로 디렉토리를 팠습니다.
계산기로 활용하던 파이썬을 훌륭한 스크립트 언어로 탈바꿈 할 수 있을까요?

## 목표

- [ ]  컴퓨팅적 사고 수업 A 이상 수료하기
- [ ]  알고리즘 문제 풀 때 빠르게 아이디어를 검증하는 용도로 활용하기
- [ ]  아이패드나 아이폰의 단축어 기능을 다채롭게 활용하기
- [ ]  목업 UI 따위에 들어갈 최소한의 동작 스크립트로 활용하기

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
- Halt conditions on Recursive functions. just return boolean value whether or not is on a halt condition. You can check when calling inside this recursive iteration, return true when its return value is also true


---

# ./HTML

## 개요

## TODO

