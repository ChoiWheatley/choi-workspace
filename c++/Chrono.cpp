#include "Chrono.h"

// member function definitions
namespace Chrono {
    Date::Date(int yy, Month mm, int dd) 
        : y{yy}, m{mm}, d{dd}
    {
        if (!is_date(yy, mm, dd)) throw Invalid{};
    }
    const Date& default_date() {
        static Date dd{2001, Month::jan, 1};
        return dd;
    }
    Date::Date()
        :y{default_date().y},
        m{default_date().m},
        d{default_date().d} 
    {};

    // you must implement those functions!

    void Date::add_day(int n) {}
    void Date::add_month(int n) {}
    void Date::add_year(int n) {
        if (m == Month::feb && d == 29 && !leapyear(y+n)) {
            m = Month::mar;
            d = 1;
        }
        y += n;
    }
    bool is_date(int y, Month m, int d) {
        
    }
    bool leapyear(int y) {}
    bool operator==(const Date&, const Date& b) {}
    bool operator!=(const Date&, const Date& b) {}
    ostream& operator<<(ostream& os, const Date& d) {}
    istream& operator>>(istream& is, const Date& d) {}
};