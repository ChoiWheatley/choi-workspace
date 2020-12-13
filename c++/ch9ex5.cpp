#include "ch9ex5.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace Libre {
    Book::Book() : 
    ISBN_{"0-0-0-x"},
    title_{"please change title"},
    author_{"please change author name"},
    copyright_date_{Chrono::Date{}}
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
		if (!valid_isbn(book.isbn())) return false;
		if (!Chrono::is_date(book.copyright_date().year(),
							book.copyright_date().month(),
							book.copyright_date().day())) return false;
		return true;
    }
    bool valid_isbn(string isbn) {
		constexpr int ascii_0 = 48;
		constexpr int ascii_9 = 57;
		constexpr int max_count = 3;
		constexpr char dash = '-';
		for (char& c : isbn) {
			static int cnt_flag = 0;
			if (cnt_flag < max_count &&
				ascii_0 <= c && c <= ascii_9) continue;
			if (cnt_flag < max_count &&
				c == dash) { 
				cnt_flag++; 
				continue; 
			}
			return false;
		}
		return true;
    }
    bool operator== (const Book& a, const Book& b) {
		return (a.isbn() == b.isbn() &&
				a.author() == b.author() &&
				a.copyright_date() == b.copyright_date() &&
				a.title() == b.title());
    }
    bool operator!= (const Book& a, const Book& b) { return !(a==b); }
    ostream& operator<< (ostream& os, const Book& book) {
		os << "[\n";
		os << book.title() << "\n";
		os << book.author() << "\n";
		os << book.isbn() << "\n]\n";
		return os;
    }
}
