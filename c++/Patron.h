/*
 * This file is for solving PPPUC++ Chapter9 Example8 
 * Author : Choi Wheatley (chltmdgus604@naver.com)
 * created : 2020 . dec . 15
 *
 * Create Patron class for the Libre program. the class will
 * have a user's name, library card number, and library fees (boolean for overdued)
 * Have functions for access this data, as well as a function to set the fee
 * of the user. Also have a helper function that returns a Boolean depending on
 * whether or not the user owes a fee
 *
 *  << Dependencies >>
 * Chrono.h : std_lib_facilities.h 
 * Chrono.cpp : Chrono.h
 * Libre.h : Chrono.h
 * Libre.cpp : Libre.h, Patron.h
 *      struct Transaction : class Book, class Patron, class Date 
 * Libre_main.cpp : Libre.h
 * Patron.h : 
 * Patron.cpp : Patron.h
 *
 *
 *
 *
 *
 */
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif

namespace LibreUser {
    typedef unsigned int T_card;
    class INV_CARD_NUM{};

    class Patron {
        string name_;                // no whitespaces between name
        T_card card_num_;      		 // 6-digit number, not 0 in front
        bool overdue_;               // assume that user always overdue when check out any books
    public:
		/* getter */
		string name() const {return name_;}
		T_card card_num() const {return card_num_;}
		bool overdue() const {return overdue_;}

		/* operator */
		inline void set_overdue_to(bool in_out);

		/* constructor */
		Patron();
		Patron(string name, T_card card_num, bool overdue = false);
	};
    // class Patron

	/* helper functions */
	bool is_overdue(const Patron& patron);

    /* misselaneouses */
    const static string default_name = "please change name";
    constexpr static T_card default_card = 100000;
    constexpr static T_card card_min = 100000;
    constexpr static T_card card_max = 999999;
}
// namespace LibreUser

