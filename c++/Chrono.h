/*
PPPUC++ Chapter 9 "Technicalities, classes and etc" 의 Date class 구현하면서 
만든 파일입니다. Helper Function 디자인 컨셉에 맞추어 코드를 구현하도록 
노력해보았습니다.
*/
#ifndef STD_LIB_FACILITIES
#define STD_LIB_FACILITIES
#include "std_lib_facilities.h"
#endif
#include <ctime>

namespace Chrono {
    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };
    /* error class */
    class INV_CMD{};    // for wrong command (today, randday)

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
    int month_day(int y, Month m, int d);
    int month_day(Date d);
    bool operator==(const Date&, const Date& b);
    bool operator!=(const Date&, const Date& b);
    ostream& operator<<(ostream& os, const Month& m);
    ostream& operator<<(ostream& os, const Date& d);
    istream& operator>>(ostream& is, Month& m);
    istream& operator>>(istream& is, Date& d);
    Date prompt_date();
    Date today();
    Date randday();
    const static string cmd_today = "today";
    const static string cmd_randday = "randday";
    const static string cmd_help = "help";
};
// Chrono
