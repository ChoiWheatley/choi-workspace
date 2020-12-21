/*
 * This is a bunch of Libre::Book, LibPat::Patron 
 * predefined classes. 
 * After I learned fstream (as file stream input and output) 
 * I will change it to txt file
 */

#ifndef LIBRE_H
#define LIBRE_H
#include "Libre.h"
#endif

namespace LibPre {
    using namespace Libre;
    using namespace LibPat;
    using namespace Chrono;
    vector<Book> init_books() {
        static vector<Book> ret;
        ret.push_back(Book{"12-45-333-x", "Computer", "Kim",                    Date{2020, Month::dec, 21}, Genre::fiction});
        ret.push_back(Book{"89-100-001-f", "Programming", "Orange_software",    Date{2019, Month::feb, 1}, Genre::biography});
        ret.push_back(Book{"25-65-23-g", "PPPUC++", "Stroustrup",               Date{2018, Month::jan, 23}, Genre::children});
        ret.push_back(Book{"34-87-9-h", "Ubuntu", "Lee",                        Date{2017, Month::mar, 5}, Genre::fiction});
        ret.push_back(Book{"55-58-2-i", "Focus", "Danial",                      Date{2016, Month::apr, 16}, Genre::nonfiction});
        ret.push_back(Book{"67-90-123-j", "Black_Flower", "YongHa",             Date{2015, Month::may, 30}, Genre::periodical});
        ret.push_back(Book{"28-556-633-k", "Martian", "Andy",                   Date{2014, Month::jun, 22}, Genre::undefined});
        ret.push_back(Book{"332-23-879-l", "Coding", "Jeff",                    Date{2013, Month::jul, 14}, Genre::children});
        ret.push_back(Book{"335-14-9-m", "Coffee", "Pushikin",                  Date{2012, Month::aug, 9}, Genre::children});
        ret.push_back(Book{"123-09-45-n", "오두막편지", "법정",                 Date{2011, Month::sep, 7}, Genre::biography});
        return ret;
    }
    vector<Patron> init_patrons() {
        static vector<Patron> ret;
        ret.push_back(Patron{"choi",        101455});
        ret.push_back(Patron{"park",        101355});
        ret.push_back(Patron{"kim",         889333});
        ret.push_back(Patron{"levine",      225444});
        ret.push_back(Patron{"quinn",       900211});
        ret.push_back(Patron{"jeff",        877753});
        ret.push_back(Patron{"bjarne",      523125});
        ret.push_back(Patron{"kyobo",       853242});
        ret.push_back(Patron{"hongneung",   134466});
        ret.push_back(Patron{"hanbit",      232566});
        return ret;
    }
}