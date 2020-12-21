/*
 * Created Date : 2020. dec. 12
 * Author : ChoiWheatley
 * 
 * This program is made for solving 
 * PPPUC++ Chapter9 Exercise5 problem.
 * 
 * Book class that contains {
 * <MEMBERS>
 *      - ISBN              // form "n-n-n-x" where n is an int, 
 *                          // x is a digit or a letter
 *      - title             // string 
 *      - author            // string
 *      - copyright date    // Date class from Chrono namespace
 * <OPERATIONS>
 *      - store data on whether or not the book is checked out
 *      - returning data values
 *      - checking a book in and out
 *      - validation of data entered into a Book
 * Later, we should add operations
 *      - == operator which checking whether the ISBN numbers are the same
 *      - != operator
 *      - << operator to print out the title, author, ISBN on separate
 *          lines
 * }
 * Later, we should create an
 *  - enumerated type for the Book class called Genre. {
 *      fiction, nonfiction, periodical, biography, and children
 * }  
 * And give each book a Genre and make appropriate changes to the Book 
 *      constructor and member functions
  
████████  ██████  ██████   ██████  
   ██    ██    ██ ██   ██ ██    ██ 
   ██    ██    ██ ██   ██ ██    ██ 
   ██    ██    ██ ██   ██ ██    ██ 
   ██     ██████  ██████   ██████  
                                   
 * <TO DO LIST>
<> 기본 Book, Patron들 만들어놓고 확인해보기
<> Genre undefined option
<> 명령어 추가하기 { add book, add patron, who owes}
<> Libre.cpp 에서 checkout() 함수 구현하기

 * <WANNA DO LIST>
<> 텍스트파일에서 Books, Patrons 받아오기, 혹은 쓰기
<> 책 이름만 나열하기, 저자만 나열하기 같은 필터링 옵션
<> 책 이름, Patron 이름에 띄어쓰기 허용하기
<> Chrono::today() 함수가 오늘날짜를 리턴하도록 만들어보자
<> Chrono::randay() 함수가 아무날짜를 리턴하도록 만들어보자
 */
#include "Libre_predefined.h"
#ifndef LIBRE_H
#define LIBRE_H
#include "Libre.h"
#endif
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif
 
int main() {
	using namespace Libre;
  using namespace LibPat;
  Library lib;
  // predefined books and patrons
  for (Book &i : LibPre::init_books()){
    lib.add_book(i);
  }
  for (Patron &i : LibPre::init_patrons()){
    lib.add_patron(i);
  }
  for (auto i : lib.books()) { cout << i; }
  for (auto i : lib.patrons()) { cout << i; }

    return 0;
}
