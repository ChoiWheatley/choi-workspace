#include "Chrono.h"
#include "Patron.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace Libre {
/* definitions */
    class Book;
    class Library;
 	enum class Genre;
    struct Transaction;
/* end of definitions */

/* Enum Class Genre and by-products */
    enum class Genre {
        fiction, nonfiction, periodical, biography, children, undefined, LAST
    };
	const static vector<string> genre_str {
	 "fiction", "nonfiction", "periodical", "biography", "children", "undefined"
	};
	//initialize Genre enum class
	Genre init_genre(string genrename);
/* end of Enum Class Genre */

/* error codes */
    class ERR_WRONG_SEARCH{};
/* end of error codes*/

    class Book
    {
        string ISBN_;   // form "n-n-n-x" where n is an int
                        // x is a digit or a letter
        string title_;
        string author_;
        Chrono::Date copyright_date_;
        Genre genre_;
        bool checked_ = false;
    public:
    /* error classes */
        class INVALID{};
        class NOGENRE{};

    /* Constructors */
        Book();
        Book(string, string, string, Chrono::Date, Genre);
        static Book& default_book();   

    /* Getters */
        string isbn() const {return ISBN_;};
        string title() const {return title_;};
        string author() const {return author_;};
        Chrono::Date copyright_date() const {return copyright_date_;};
        bool is_checked() const {return checked_;};
		Genre genre() const {return genre_;}

    /* Operators */
        // in = true, out = false
        void check_to(bool in_out) {checked_ = in_out;}
		void init_book(Book& book);
    };
    // class Book

/* Book helper functions */    
    // in = true, out = false
    // return value as succession
    bool checking(Book& book, bool in_out); 
    // validation of data entered into a Book
    // especially isbn code
    bool validate(const Book&);
    bool valid_isbn(string isbn);
    /* default variables */
    const static string default_isbn = "0-0-0-x";
    const static string default_title = "Please_change_title";
    const static string default_author = "Please_change_author_name";
    const static Chrono::Date default_copyright_date = Chrono::Date{};
    const static Genre default_genre = Genre::undefined;
/* end of Book helper functions */

    class Library{
        vector<Book> books_;
        vector<LibPat::Patron> patrons_;
        vector<Transaction> transactions_;

        public:

        /* error codes */
        class INV_BOOK{};
        class INV_PATRON{};

        /* getters */
        vector<Book> books() const{return books_;}
        vector<LibPat::Patron> patrons() const{return patrons_;}
        vector<Transaction> transactions() const{return transactions_;}
        // check all patrons who already have checked out a book
        vector<LibPat::Patron> who_owe() const;
        
        /* operations */
        // no duplicate!
        void add_book(Book& book);
        // no duplicate!
        void add_patron(LibPat::Patron& patron);
        // 1. Is book available in the Library?
        // 2. Is patron exist?
        // finally, add Transaction into a transactions_
        void check_out(const Book& book, const LibPat::Patron& patron, const Chrono::Date& = Chrono::Date{}); 

        /* constructor */
        Library();
    };
    // class Library

    typedef struct Transaction
    {
        Libre::Book book;
        LibPat::Patron patron;
        Chrono::Date check_date;
    } Transaction;
/* Library helper functions */
    // find book for isbn or title or author
    Book& find_book(const Library&, string);
    // find patron for name
    LibPat::Patron& find_patron_by_name(const Library&, string name);
    LibPat::Patron& find_patron_by_card(const Library&, LibPat::T_card card);
/* end of Library helper functions */


    
/* Miscellaneous */
    // check whether the ISBN numbers are the same
    bool operator== (const Book&, const Book&);
    bool operator!= (const Book&, const Book&);
    // print out the title, author, ISBN on separate lines
    ostream& operator<< (ostream&, const Book&);
	// print out the Genre
	ostream& operator<< (ostream&, Genre);
    // print out Transaction values
    ostream& operator<< (ostream&, Transaction);
    // print out Patron values
    ostream& operator<< (ostream&, LibPat::Patron&);
}
// namespace Libre
