#ifndef LIBRE_H
#define LIBRE_H
#include "Libre.h"
#endif
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace Libre {

/* Constructors */

    Book::Book() : 
    ISBN_{default_isbn},
    title_{default_title},
    author_{default_author},
    copyright_date_{default_copyright_date},
    genre_{default_genre}   
    {};

    Book::Book(string isbn, string title, string author, Chrono::Date copydate, Genre genre) :
    ISBN_{isbn},
    title_{title},
    author_{author},
    copyright_date_{copydate},
	genre_{genre}
    {
        if (!validate(*this)) throw INVALID{};
    };
	Book& Book::default_book(){
        static Book ret{default_isbn, default_title, default_author, default_copyright_date, default_genre};
        return ret;
	}
	Library::Library():
	books_{}, patrons_{}, transactions_{}{};

	/* Book */
    //
	Book& init_book() {
		char answer = 'n';
		string isbn;
		string title;
		string author;
        string str_genre;
		Genre genre;
		Chrono::Date copyright_date;
		while (cin) {
			try {
				cout << "Hello! Please input isbn serial code : ";
				cin >> isbn;
				cout << "Please input title : ";
				cin >> title;
				cout << "Please input author : ";
				cin >> author;
				cout << "Please input copyright date\n";
				copyright_date = Chrono::prompt_date();
                cout << "Please input genre kind (";
                for (auto i : genre_str){cout << i << ", ";}
                cout << "\b\b)\n>>";
                cin >> str_genre;
				genre = init_genre(str_genre);
				Book *newBook = new Book{ isbn, title, author, copyright_date, genre };
				cout << *newBook;
				cout << "did you write all the contents properly? (y/n) : ";
				cin >> answer;
				if (answer == 'Y' || answer == 'y') { return *newBook; }
				if (answer == 'N' || answer == 'n') continue;
			}
			catch (Book::INVALID e){
				cout << "incorrect isbn format! try again\n";
				continue;
			}
			catch (Book::NOGENRE e){
				cout << "incorrect genre selection! try again\n";
				continue;
			}
			catch (Chrono::Date::Invalid e){
				cout << "incorrect date format! try again\n";
				continue;
			}
			catch (...){
				error ("Something bad happens! Sorry\n");
			}
		}
		return Book::default_book();
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
		int cnt_flag = 0;
		for (char& c : isbn) {
			if (cnt_flag < max_count &&
				ascii_0 <= c && c <= ascii_9) continue;
			if (cnt_flag < max_count &&
				c == dash) { 
				cnt_flag++; 
				continue; 
			}
			if (cnt_flag == max_count) {
				cnt_flag++;
				continue;
			}
			return false;
		}
		return true;
    }
	//
	/* end of Book */
	
	/* Library */
	//
	// check all patrons who already have checked out a book
	vector<LibPat::Patron> Library::who_owe() const{
		vector<LibPat::Patron> owed;
		for (auto i : patrons_){
			if (LibPat::is_overdue(i)) owed.push_back(i); 
		}
		return owed;
	}
	// no duplicate!
	void Library::add_book(Book& book) {
		for (auto i : books_) {
			if (i == book) throw INV_BOOK{};
		}
		books_.push_back(book);
	}
	// no duplicate!
	void Library::add_patron(LibPat::Patron& patron) {
		for (auto i : patrons_) {
			if (i == patron) throw INV_PATRON{};
		}
		patrons_.push_back(patron);
	}
	// prerequisite :
	// 1. Is book available in the Library? (not checked out)
	// 2. Is patron available? (not owed)
	// operation : 
	// 1. add Transaction into transactions_
	// 2. checkout book
	// 3. owe patron (assume that user always overdue)
	void Library::check_out(Book& book, LibPat::Patron& patron, const Chrono::Date& date) {
		if (book.is_checked() || patron.overdue()) throw ERR_CHECKED_ALREADY{};
		Transaction newcheck{book, patron, date};
		book.check_to(true);
		patron.set_overdue_to(true);
		transactions_.push_back(newcheck);
	}
	// find book for isbn, title, or author
	Book& Library::find_book(){
		cout << "You can find book for author name, isbn, title\n\t>>";
		string input;
		cin >> input;
		return find_book(input);
	}
	Book& Library::find_book(string k){
		for (Book& i : books_){
			if (k == i.isbn()) return i;
			if (k == i.title()) return i;
			if (k == i.author()) return i;
		}
		throw ERR_WRONG_SEARCH{};
		return Book::default_book();
	}
	// find patron for name or card number
	LibPat::Patron& Library::find_patron(){
		cout << "You can find patron for patron name, card number\n\t>>";
		string input;
		cin >> input;
		return find_patron(input);
	}
	LibPat::Patron& Library::find_patron(string name){
		for (LibPat::Patron& i : patrons_){
			if (name == i.name()) return i;
			if (name == to_string(static_cast<int>(i.card_num()))) return i;
		}
		throw ERR_WRONG_SEARCH{};
		return LibPat::Patron::default_Patron();
	}
    LibPat::Patron& find_patron_by_card(const Library& lib, LibPat::T_card card){
		for (LibPat::Patron& i : lib.patrons()){
			if (card == i.card_num()) return i;
		}
		throw ERR_WRONG_SEARCH{};
		return LibPat::Patron::default_Patron();
	}
	
/* end of Library */
	
/* genre */
	Genre init_genre(string genrename) {
		for (int i = 0; i < genre_str.size(); i++) {
		 	if (genrename == genre_str[i]) return static_cast<Genre>(i);
		}
		throw Book::NOGENRE{};
		return Genre::fiction;
	}
/* end of genre */

/* Miscellaneous */
    bool operator== (const Book& a, const Book& b) {
		return (a.isbn() == b.isbn() &&
				a.author() == b.author() &&
				a.copyright_date() == b.copyright_date() &&
				a.title() == b.title());
    }
    bool operator!= (const Book& a, const Book& b) { return !(a==b); }
    ostream& operator<< (ostream& os, const Book& book) {
		os << "Book [\n";
		os << '\t' << "title:     \t"<< book.title() << "\n";
		os << '\t' << "author:    \t" << book.author() << "\n";
		os << '\t' << "copyright: \t" << book.copyright_date() << "\n";
		os << '\t' << "genre :    \t" << book.genre() << "\n";
		os << '\t' << "isbn :     \t" << book.isbn() << "\n";
		os << '\t' << "checked out\t" << (book.is_checked() ? "yes" : "no") << "\n";
		os << "]\n";
		return os;
    }
	ostream& operator<< (ostream& os, Genre gen) {
		os << genre_str[static_cast<int>(gen)];
		return os;
	}
	ostream& operator<< (ostream& os, Transaction tran) {
		os << "Transaction [\n";
		os << '\t' << "book :       \t" << tran.book.title() << '\n';
		os << '\t' << "patron:      \t" << tran.patron.name() << '\n';
		os << '\t' << "checkoutdate:\t" << tran.check_date << '\n';
		return os;
	}
	
	//
	/* end of Miscellaneous */
}
/* namespace Libre */
