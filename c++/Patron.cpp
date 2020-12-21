#include "Patron.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace LibPat {
	inline void Patron::set_overdue_to(bool in_out){ overdue_ = in_out; }

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
	bool is_overdue(const Patron& patron){return patron.overdue();}
    // check whether Patron is duplicated
    bool operator== (const Patron& a, const Patron& b) {
		if (a.name() != b.name()) return false;
		if (a.card_num() != b.card_num()) return false;
		return true;
	}
    bool operator!= (const Patron& a, const Patron& b) { return !(a==b); }
}
