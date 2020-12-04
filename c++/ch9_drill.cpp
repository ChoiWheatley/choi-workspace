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
#include "ch9_drill.h"

int month_day(Date d) 
{
	int month_day = 30;
	switch (d.month()) {
		case Month::jan: case Month::mar: case Month::may: case Month::jul: case Month::aug: case Month::oct: case Month::dec:
			month_day = 31;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			month_day = 30;
			break;
		case Month::feb:
			if (leap_year(d.year())) month_day = 29;
			else month_day = 28;
			break;
		default:
			throw Invalid_Date{};
	}
	return month_day;
}
bool leap_year(Year y)
{
	bool flag = false;
	if (y.to_int()%400 == 0) flag = true;
	if (y.to_int()%100 == 0) flag = false;
	if (y.to_int()%4 == 0) flag = true;
	return flag;
}
void Date::add_day(int n) {
	// pre-condition : 날짜를 더했는데 달을 넘어간다
	int md = month_day(today());
	for (; d + n > md; ) {
		add_month(1);
		n -= md - d;
		d = 0;
		md = month_day(today());
	}
	d = n;
}
void Date::add_month(int n) {
	// pre-condition : above december
	int month = static_cast<int>(m);
	if ((month+n) % 12 == 0) m = Month::dec;
	else { m = static_cast<Month>((month+n) % 12); }
	add_year(floor((month+n)) / 13);
	// DEBUG
	cout << now();
}

ostream& operator<< (ostream& os, Date& date) {
	os << date.year().to_int() << ". " << static_cast<int>(date.month()) << ". " << date.day() << endl;
	return os;
}



//
//
int main()
{
	int yy, mm, dd;
	while(cin) {
		cout << "Please input three integers : ";
		cin >> yy >> mm >> dd;
		Date today{Year{yy}, static_cast<Month>(mm), dd};
		cout << today << '\n';
		int ad = 0;
		cout << "Please input number you want to add day : ";
		cin >> ad;
		today.add_day(ad);
		cout << today << '\n';
		cout << "Please input number you want to add month: ";
		cin >> ad;
		today.add_month(ad);
		cout << today << '\n';
		cout << "Please input number you want to add year: ";
		cin >> ad;
		today.add_year(ad);
		cout << today << '\n';
	}
	return 0;
}
//