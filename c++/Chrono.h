/*
PPPUC++ Chapter 9 "Technicalities, classes and etc" 의 Date class 구현하면서 
만든 파일입니다. Helper Function 디자인 컨셉에 맞추어 코드를 구현하도록 
노력해보았습니다.
*/
#include "std_lib_facilities.h"

namespace Chrono {
    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };
    class Date {
    public:
        class Invalid{}; // to throw an exception
        Date(int yy, Month mm, int dd);    // check for valid date and initialize
        Date();                         // default constructor

        // nonmodifying operations : getter

        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }

        //modifying operations : setter

        void add_day(int n);
        void add_month(int n);
        void add_year(int n);

    private:
        int y;
        Month m;
        int d;
    };

    // Helper Functions

    bool is_date(int y, Month m, int d);    // true for valid date
    bool leapyear(int y);                   // true for leap year (윤년)
    bool operator==(const Date&, const Date& b);
    bool operator!=(const Date&, const Date& b);
    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(istream& is, const Date& d);
};
// Chrono