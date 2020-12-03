class Invalid_Date{};
class Date;
enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};
class Year {
	static constexpr int min = 1000;
	static constexpr int max = 2900;
public:
	class Invalid_Year{};
	Year(int yy) : y{yy} { if (yy < min || max <= yy) throw Invalid_Year{}; }
	void addyear(int n) {y += n;}
	int to_int() {return y;}
private:
	int y;
};
class Date {
	private:
		Year y;
		Month m;
		int d;
	public:
		Date(Year yy, Month mm, int dd): y{yy}, m{mm}, d{dd} {};
		void add_day(int n);
        void add_month(int n);
        void add_year(int n) {y.addyear(n);}
		Month month() {return m;}
		int day() {return d;}
		Year year() {return y;}
        Date& today() {return *this;}
        Date& now() {return *this;}
};
bool valid_date(Date d);
bool leap_year(Year y);
int month_day(Date d);

ostream& operator<< (ostream& os, Date& date);