#include "Patron.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace LibPat {
	void Patron::set_overdue_to(bool in_out){ overdue_ = in_out; }

	/* constructor */
	Patron::Patron(): 
	name_{default_name},
	card_num_{default_card},
	overdue_{false}
	{}
	Patron::Patron(string name, T_card card_num, bool overdue):
	name_{name},
	card_num_{card_num},
	overdue_{overdue}
	{
		if (!(card_min <= card_num_ &&
			card_num_ <= card_max)) throw INV_CARD_NUM{};
	}
    Patron& Patron::default_Patron(){
        static Patron ret{default_name, default_card};
        return ret;
    }

	/* helper functions */
	Patron& init_Patron()
	{
		char answer = 'n';
		string name;
		T_card card = default_card;
		while (cin) {
			try{
				cout << "Hello! Please input Patron's name:\n>>";
				cin >> name;
				cout << "Please input card number. card number is 6 digit number between 100000 and 999999 \n>>";
				cin >> card;
				Patron *newPatron = new Patron{name, card};
				cout << *newPatron;
				cout << "did you write all the contents properly? (y/n) : ";
				cin >> answer;
				if (answer == 'Y' || answer == 'y') { return *newPatron; }
				if (answer == 'N' || answer == 'n') continue;
			}
			catch(INV_CARD_NUM e){
				cout << "Sorry Card number form is 6digit, between 100000 and 999999\n";
				continue;
			}
			catch(...){
				error("Sorry!! I cannot find out what error is : ");
			}
		}
		return Patron::default_Patron();
	}
	bool is_overdue(const Patron& patron){return patron.overdue();}
    // check whether Patron is duplicated
    bool operator== (const Patron& a, const Patron& b) {
		if (a.name() != b.name()) return false;
		if (a.card_num() != b.card_num()) return false;
		return true;
	}
    bool operator!= (const Patron& a, const Patron& b) { return !(a==b); }
	ostream &operator<<(ostream &os, LibPat::Patron &pat){
		os << "Patron [\n";
		os << '\t' << "name :      \t" << pat.name() << '\n';
		os << '\t' << "card number:\t" << pat.card_num() << '\n';
		os << '\t' << "overdue? :  \t" << (pat.overdue() ? "yes" : "no") << '\n';
		os << "]\n";
		return os;
	}
}
