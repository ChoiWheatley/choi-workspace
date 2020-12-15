#include "Patron.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace LibreUser {
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

	/* helper functions */
	bool is_overdue(const Patron& patron){return patron.overdue();}
}
