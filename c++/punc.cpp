/*
 * <PPPUC++> Chapter11 Exercise6 
 * Write a program that replaces punctuation with whitespace. 
 * Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters. 
 * Don’t modify characters within a pair of double quotes ("). 
 * For example, “ - don't use the as-if rule.” becomes “ don t use the as if rule ”.
 * 
 * << First attempt 2021. 01. 12 >>
 * 
 * <<Thinking>>
 * <> Can I eliminate ' ' as whitespace? And is it worth it?
 *      use "istream::unsetf(ios::skipws)"
 * <> Can I inherit Puncstream from istream?? how?
 *      Inheritance from istream and "streambuffer" --> I cann't do it now...
 */

#include "std_lib_facilities.h"

namespace PUNC {

    class Puncstream {
    public:
        Puncstream(istream& is) : source{is} {}
        Puncstream(istream& is, string punc, bool sensitive = false) : 
            source{is}, punctuation{punc}, case_sensitive{sensitive} {};
        inline bool is_punc(char c);
        operator bool();
        Puncstream& operator>>(string&);
    private:
        string punctuation = ".;,?-'";
        istream& source;
        istringstream buffer;
        bool case_sensitive;
    };

}


int main() 
{
    ifstream ifs{"sample.txt"};
    ofstream ofs{"output.txt"};
    if(!ifs) error("error while opening this file");
    PUNC::Puncstream ps{ifs, ".;?,-'"};
    for (string str; ps >> str; ) {
        static int cnt = 1;
        if ((cnt++ %10) == 0) ofs << '\n';
        ofs << str << '\t';
    }
    return 0;
}



namespace PUNC{
    inline bool Puncstream::is_punc(char c) {
        for (char i : Puncstream::punctuation) if (c == i) return true;
        return false;
    }
    Puncstream& Puncstream::operator>>(string & str) {
        while(!(buffer >> str)) {
            if (buffer.bad() || !source.good()) return *this;
            buffer.clear();
            // replenish buffer 
            string line;
            getline(source, line);

            // do character replacement as needed
            for (char& ch : line) {
                if (is_punc(ch)) ch = ' ';
                else if (case_sensitive)
                    ch = tolower(ch);
            }
            buffer.str(line);       // put string into stream
        }
        return *this;
    }
    Puncstream::operator bool() {
        return !(source.fail() || source.bad()) && buffer.good();
    }
}

