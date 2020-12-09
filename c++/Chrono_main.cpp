/*
 * 
 * 
 */

#include "Chrono.h"
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif
using namespace Chrono;

//
//
int main()
{
	Date newDate;
	cin >> newDate;
	cout << newDate;
	while (cin) {
		string command;
		cin >> command;
		if (command == "exit" || 
			command == "quit" ||
			command == "bye"
		) return 0;
		if (command == "ad") {
			cout << "Please input number you want to add day : ";
			int ad;
			cin >> ad;
			newDate.add_day(ad);
		}
		if (command == "am") {
			cout << "Please input number you want to add month : ";
			int am;
			cin >> am;
			newDate.add_month(am);
		}
		if (command == "ay") {
			cout << "Please input number you want to add year : ";
			int ay;
			cin >> ay;
			newDate.add_year(ay);
		}
		if (command == "new") {
			cout << "Please input three numbers you want to place new date : ";
			cin >> newDate;
		}
		if (command == "help") {
			cout << "ad : add day\nam : add month\nay : add year\n";
			continue;
		}
		cout << newDate;
	}
	return 0;
}
//
//
