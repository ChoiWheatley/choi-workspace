# choi-workspace/Readme.md

# ./python

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

### 종만북 ("apss/")
도서 '프로그래밍 대회에서 배우는 알고리즘 문제해결전략' (프알문, APSS) 로 공부를 시작했고, 최근에 21년 2월 10일부터 3월 말까지(45일) 백준 인강을 구독했기에 해당 문제들 위주로 정리해서 올릴 예정이다.

### 21년 여름학기 코테 강의 ("CoTe/") 

**강의 사이트** : [programmers.co.kr/learn/challenges](http://programmers.co.kr/learn/challenges) 

**다루는 알고리즘** : 해시, 스택-큐, 힙, 정렬, 완전탐색, 그리디, 다이나믹 프로그래밍, DFS-BFS, 이진탐색, 그래프

**강의 진행 언어** Python

**강의 부교재** 이것이 코딩테스트다 with 파이썬 (한빛미디어, 나동빈)

**코딩 테스트 준비 방법** 기업, 문법암기, 이론을 말로 설명하기, 문제 직접 풀어보기, 자신만의 소스코드 라이브러리화 하기

네이버 10월 6일 온라인 테스트.

## 강의진행순서

1. 알고리즘 개요 전체 설명 → 화요일
2. 코딩 테스트 문제 설명 → 화요일
3. 개인이 직접 코딩 후 [programmers.co.kr](http://programmers.co.kr) 사이트에 직접 제출 → 목요일 10시 전까지
4. 코딩 테스트 문제에 대한 해답을 설명 → 목요일

**당부사항** 강의 시작 전에 개개인마다 강의 예정인 코딩테스트 문제 내용 파악. 

**당부사항** 파이썬 자료형, 자료구조, 알고리즘, 라이브러리 등에 대한 기본적인 사항을 병행해 가며 공부할 것!!

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

