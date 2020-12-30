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
 *      - == operator which checking whether the ISBN numbers are the same
 *      - != operator
 *      - << operator to print out the title, author, ISBN on separate
 *          lines
 *      - enumerated type for the Book class called Genre. {
 *      fiction, nonfiction, periodical, biography, and children
 *      }
 * }  
 * 
 * [ Error Flows ]
 * 
 * < namespace Libre >
 * ┠ ERR_WRONG_SEARCH{} := throwed in find_book(), find_patron()  
 * ┃                       / catched in main(), checkout()
 * ┠ class Book
 * ┃ ┠ INVALID{} := throwed in constructor Book() / catched in init_book()
 * ┃ ┗ NOGENRE{} := throwed in init_genre() / catched in init_book()
 * ┗ class Library
 *   ┠ INV_BOOK{} := throwed in add_book(), catched in main()
 *   ┗ INV_PATRON{} := throwed in add_patron(), catched in main()
 * 
 * < namespace LibPat >
 * ┗ INV_CARD_NUM{} := throwed in constructor Patron() / catched in init_Patron()
 * 
 * < namespace Chrono >
 * ┗ class Date
 *   ┗ Invalid{} := throwed in constructor Date(), month_day() 
 *               / catched in init_book(), checkout()
 * 
 * < namespace CMD >
 * ┗ ERR_NO_COMMAND{} := throwed in cmdtoenum() / catched in main()
 * 
  
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
<>  챕터6에서 배웠던 문법 파싱 기법을 사용해도 좋지 않을까?
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

namespace CMD{
  class ERR_NO_COMMAND{};
  enum class CommandSets {
    add_book, 
    add_patron,
    who_owes,
    print_books,
    print_patrons,
    print_transactions,
    find_book,
    find_patron,
    checkout,
    help, 
    exit
  };
  const static vector<string> command_sets{
      "add_book",
      "add_patron",
      "who_owes",
      "print_books",
      "print_patrons",
      "print_transactions",
      "find_book",
      "find_patron",
      "checkout",
      "help",
      "exit"
      };
  CommandSets cmdtoenum(string str){
    for (int i = 0; i < command_sets.size(); i++) {
      if (str == command_sets[i]) return (static_cast<CommandSets>(i));
    }
    throw ERR_NO_COMMAND{};
    return CommandSets::add_book;
  }
  void help(){
    for (auto i : command_sets) {cout << i << '\n';}
  }
} // namespace CMD

 
int main() {
  using namespace Libre;
  using namespace LibPat;
  using namespace CMD;
  /* initialize process : 
   * define books and patrons from Libre_predefined.cpp
   */
  Library lib;
  for (Book &i : LibPre::init_books()){
    lib.add_book(i);
  }
  for (Patron &i : LibPre::init_patrons()){
    lib.add_patron(i);
  }

  while (cin){
    try{
      /* command interpretation */
      string cmd;
      CommandSets cmdnum;
      cout << ">>";
      cin >> cmd;
      switch (cmdtoenum(cmd)){
        case CommandSets::add_book :
          lib.add_book(init_book());
          break;
        case CommandSets::add_patron :
          lib.add_patron(init_Patron());
          break;
        case CommandSets::checkout :
        {
          cout << "which book do you like to check out? :\n";
          Book& newbook = lib.find_book();
          cout << "who do you like to check out? : \n";
          Patron& newPatron = lib.find_patron();
          cout << "when is the checkout day?\n";
          lib.check_out(newbook, newPatron, Chrono::prompt_date());
          break;
        }
        case CommandSets::find_book :
          cout << lib.find_book();
          break;
        case CommandSets::find_patron :
          cout << lib.find_patron();
          break;
        case CommandSets::print_books :
          for (auto i : lib.books()) cout << i;
          break;
        case CommandSets::print_patrons :
          for (auto i : lib.patrons()) cout << i;
          break;
        case CommandSets::print_transactions :
          for (auto i : lib.transactions()) cout << i;
          break;
        case CommandSets::who_owes :
          for (auto i : lib.patrons()){
            if (i.overdue()) cout << i;
          }
          break;
        case CommandSets::help :
          help();
          break;
        case CommandSets::exit :
          return 0;
        default:
          throw ERR_NO_COMMAND{};
      }
    }
    catch(ERR_WRONG_SEARCH e){
      cout << "Please try again : no word found\n";
      continue;
    }
    catch(Library::INV_BOOK e){
      cout << "Book duplicated!\n";
      continue;
    }
    catch(Library::INV_PATRON e) {
      cout << "Patron duplicated!\n";
      continue;
    }
    catch(CMD::ERR_NO_COMMAND e) {
      cout << "Wrong command. Please try again\n";
      continue;
    }
    catch(exception e){
      cout << "Exception code : " << e.what() << '\n';
      error("Ooooops... I cannot find out what have crashed\n");
    }
  };

    return 0;
}