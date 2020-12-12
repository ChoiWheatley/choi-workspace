#include "ch9ex5.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace Libre {
    Book::Book() : 
    ISBN_{default_isbn},
    title_{default_title},
    author_{default_author},
    copyright_date_{default_copy_date} 
    {};
    Book::Book(string isbn, string title, string author, Chrono::Date copydate) :
    ISBN_{isbn},
    title_{title},
    author_{author},
    copyright_date_{copydate} 
    {
        if (!validate(*this)) throw INVALID{};
    };

    bool checking(Book& book, bool in_out) {
        if (in_out == true && book.is_checked()) return false;
        book.check_to(in_out);
        return true;
    }
    bool validate(const Book& book) {
        
    }
    bool valid_isbn(string isbn) {

    }
    bool operator== (const Book& a, const Book& b) {

    }
    bool operator!= (const Book& a, const Book& b) { return !(a==b); }
    ostream& operator<< (ostream& os, const Book& book) {

    }
}