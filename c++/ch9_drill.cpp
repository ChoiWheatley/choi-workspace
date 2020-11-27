/*
 * make a valid date check program from 9.4.1 ~ 9.4.5
 * 
 * This drill simply involves getting the sequence of versions of Date to work. 
 * For each version define a Date called today initialized to June 25, 1978. 
 * Then, define a Date called tomorrow and give it a value by copying today 
 * into it and increasing its day by one using add_day(). 
 * Finally, output today and tomorrow using a << defined as in §9.8. 
 * Your check for a valid date may be very simple. Feel free to ignore leap years. 
 * However, don’t accept a month that is not in the [1,12] range or day of the month 
 * that is not in the [1,31] range. Test each version with at least one invalid date 
 * (e.g., 2004, 13, –5).
 */

#include "std_lib_facilities.h"
class Invalid_Date{};
struct Date {
	int y;	// year
	int m; 	// month
	int d;	// day
	Date(int y, int m, int d);
	void add_day(int n);
	int month_day();
	bool is_valid();
};

Date::Date(int yy, int mm, int dd) {
	y = yy;
	m = mm;
	d = dd;
	if (!is_valid()) throw Invalid_Date{};
}
void Date::add_day(int n) {
	d += n;
	int md = month_day();
	if (d > md) {
		m += static_cast<int>(d / md);
		d = (d+n) % md;
	}
}
int Date::month_day(){
	int month_day = 30;
	switch (m) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			month_day = 31;
			break;
		case 4: case 6: case 9: case 11:
			month_day = 30;
			break;
		case 2:
			month_day = 28;
			break;
		default:
			throw Invalid_Date{};
	}
	return month_day;
}

bool Date::is_valid() {
	if (!(d >= 1 && d <= month_day())) return false;
	return true;
}

void print_date(Date date) {
	cout << date.y << ". " << date.m << ". " << date.d << endl;
}

ostream& operator<< (ostream& os, Date& date) {
	os << date.y << ". " << date.m << ". " << date.d << endl;
	return os;
}

//
//
int main()
{
	int yy, mm, dd;
	cout << "Please input three integers : ";
	cin >> yy >> mm >> dd;
	Date today{yy, mm, dd};
	cout << today << '\n';
	int ad = 0;
	cout << "Please input number you want to add day : ";
	cin >> ad;
	today.add_day(ad);
	cout << today << '\n';

	
	return 0;
}
//
//
