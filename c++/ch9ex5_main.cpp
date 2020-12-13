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
 * <> Make file is neccessary because I have to compile both Chrono*.cpp and ch9ex5*.cpp files
 * <> enum class Genre 만들기
 */

#include "ch9ex5.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif
 
int main() {
	using namespace Libre;
	Book newBook{};
	cout << newBook;
    return 0;
}
