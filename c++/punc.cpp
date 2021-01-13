/*
 * <PPPUC++> Chapter11 Exercise6 
 * Write a program that replaces punctuation with whitespace. 
 * Consider . (dot), ; (semicolon), , (comma), ? (question mark), - (dash), ' (single quote) punctuation characters. 
 * Don’t modify characters within a pair of double quotes ("). 
 * For example, “ - don't use the as-if rule.” becomes “ don t use the as if rule ”.
 * 
 * << Second attempt 2021. 01. 13 >>
 * - Problem : The last line cannot printed at all. I think src_ met eof() and the next loop, 
 *      because the exit condition is satisfacted, the program exit the loop.
 * 
 * << First attempt 2021. 01. 12 >>
 * - something has wrong with this program. Puncstream vomitted during eating process and
 *      straightly met end of loop.
 * 
 * <<Thinking>>
 * <> Can I eliminate ' ' as whitespace? And is it worth it?
 *      use "istream::unsetf(ios::skipws)"
 * <> Can I inherit Puncstream from istream?? how?
 *      Inheritance from istream and "streambuffer" --> I cann't do it now...
 */

#include "std_lib_facilities.h"

namespace Punc
{
    enum class P_ERR {
        good,
        eof,
        fail,
        bad
    };
    class Puncstream
    {
    public:
        Puncstream(istream &is, bool case_sensitive = false, string punctuation = ".,;!?|~'-") : src_{is}, punctuation_{punctuation}, case_sensitive_{case_sensitive} {}
        bool is_case_sensitive() const { return case_sensitive_; }
        operator bool() {return !(src_.eof() || src_.bad() || buffer_.bad());}
        bool is_punctuation(char) const;
        istringstream& get_buffer() {return buffer_;}
        // from src_, we convert defined whitespace into buffer each line,
        // and we do buffer >> str until buffer is nothing left.
        Puncstream& operator>> (string& str);
    private:
        istream &src_;
        istringstream buffer_;
        bool case_sensitive_;
        string punctuation_;
    };  // class Puncstream
    void show_buffer(istringstream& buffer);
} // namespace Punc
int main() 
{
    ifstream ifs{"sample.txt"};
    ofstream ofs{"output.txt"};
    if (!ifs || !ofs) error("error opening the file");
    Punc::Puncstream ps{ifs, true};
    for (string str; ps >> str; )
    {
        static int cnt = 0;
        ofs << str << '\t';
        if ((++cnt %20) == 0) ofs << '\n';
    }
    return 0;
}


namespace Punc 
{
    bool Puncstream::is_punctuation(char c) const {
        for (auto i : punctuation_) 
            if (c == i) return true;
        return false;
    }
    // from src_, we convert defined whitespace into buffer each line,
    // and we do buffer >> str until buffer is nothing left.
    Puncstream &Puncstream::operator>>(string& str) {
        while (!(buffer_ >> str)) {
            if (buffer_.bad() || !src_.good()) return *this;
            buffer_.clear();
            string line;
            getline(src_, line);
            // punctuation into whitespace 
            for (char& c : line) {
                if (is_punctuation(c)) c = ' ';
                if (is_case_sensitive()) c = tolower(c);
            }
            buffer_.str(line);
        }
        return *this;
    }
    void show_buffer(istringstream& buffer) {
        for (string str; buffer >> str; ) {
            static int cnt = 0;
            cout << str << '\t';
            if ((++cnt %20) == 0) cout << "\n";
        }
    }
}