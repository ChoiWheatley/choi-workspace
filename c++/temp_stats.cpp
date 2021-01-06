/*
 * PPPUC++ Chapter10 Exercise 3
 * Write a program that reads the data from "raw_temps.txt" created in Ex2 into 
 * a vector and then calculates the mean and median temperatures in your data set.
 * Call the program "temp_stats.cpp"
 * 
 * << PPPUC++ Chapter10 Exercise4 >> add suffix 'c' and 'f' 
 * Modify the store_temps.cpp program from exercise 2 to include a temperature suffix c for Celsius 
 * or f for Fahrenheit temperatures. 
 * Then modify the temp_stats.cpp program to test each temperature, 
 * converting the Celsius readings to Fahrenheit before putting them into the vector.
 * 
 * Idea
 * ㅁ 메모리 통째로 파일에 옮겨넣을 수는 없는걸까? 
 */

#include "std_lib_facilities.h"
#include <unistd.h>

struct Reading {
    int hour;
    double temperature;
    char format;
};
constexpr char Celsius = 'c';
constexpr char Fahrenheit = 'f';

vector<Reading> get_readings(ifstream&);
bool skip(ifstream&);
double mean(vector<double>&);
double median(vector<double>&);
vector<double>& get_temperature(vector<Reading>&);
void c_to_f(vector<Reading>& r);
void f_to_c(vector<Reading>& r);
inline double c_to_f(double c);
inline double f_to_c(double f);
istream& operator>> (istream& is, Reading& r);
ostream& operator<< (ostream& os, vector<Reading>& r);
ostream& operator<< (ostream& os, Reading& r);

int main(void) {
    vector<Reading> readings;
    ifstream ifs{"raw_temps.txt"};
    if (!ifs) error("something wrong with opening the file");
    readings = get_readings(ifs);
    cout << readings;
    f_to_c(readings);
    cout << readings;
    cout << "mean : " << mean(get_temperature(readings)) << endl;
    cout << "median : " << median(get_temperature(readings)) << endl;

    return 0;
}









vector<Reading> get_readings(ifstream& ifs) {
    vector<Reading> ret;

    // when iostate goes bad, throw
    ifs.exceptions(ifs.exceptions() | ios_base::badbit);

    for (Reading r; true; ) {
        ifs >> r;
        // DEBUG
        cout << "Debug : " << r << endl;

        if (ifs.eof()) {
            // you have to figure out how to get the last data when eof() hit
            // both error occured when eof() hit
            ret.push_back(r);
            break;
        }
        else if (ifs.fail()) { // format error
            if (!skip(ifs)) break;
            else continue;
        }
        else ;// bad ==> auto throw
        ret.push_back(r);
    }
    return ret;
}
// true when successfully meet next line charactor
// false when meet eof() during skipping 
bool skip(ifstream& ifs) {
    ifs.clear();
    // skip until next line charactor appear
    for (char ch ; (ifs && ch != '\n') ; ch = ifs.get()) {
        // DEBUG
        cout << "skipped : " << ch << endl;
    }
    // if eof() hit, you have to close the reading sequence
    if (ifs.eof()) return false;
    ifs.unget();
    return true;
}
double mean(vector<double>& temp) {
    double sum = 0;
    for (auto i : temp) sum += i;
    return sum / temp.size();
}
double median(vector<double>& temp) {
    vector<double> sorted{temp};
    sort(sorted);
    return sorted[static_cast<int>(sorted.size()/2)];
}
vector<double>& get_temperature(vector<Reading>& r) {
    static vector<double> temperatures;
    for (Reading i : r) {
        temperatures.push_back(i.temperature);
    }
    return temperatures;
}
void c_to_f(vector<Reading>& r) {
    for (Reading& i : r) {
        if (i.format == Celsius) {
            i.format = Fahrenheit;
            i.temperature = c_to_f(i.temperature);
        }
    }
}
void f_to_c(vector<Reading>& r) {
    for (Reading& i : r) {
        if (i.format == Fahrenheit) {
            i.format = Celsius;
            i.temperature = f_to_c(i.temperature);
        }
    }
}
// (1°C × 9/5) + 32 = 33.8°F
inline double c_to_f(double c) {
    return ((c * 9 / 5) + 32);
}
// (1°F − 32) × 5/9 = -17.22°C
inline double f_to_c(double f) { 
    return ((f - 32) * 5 / 9);
}










istream& operator>> (istream& is, Reading& r) {
    int hr;
    double temp;
    char fmt = 0;
    is >> hr;
    // get until suffix is found
    for (; (is && fmt != Celsius && fmt != Fahrenheit); fmt = is.get());
    is >> temp;
    r.hour = hr;
    r.format = fmt;
    r.temperature = temp;
    return is;
}
ostream& operator<< (ostream& os, vector<Reading>& r) {
    int cnt = 1;
    os << "[\n";
    for (auto i : r) os << cnt++ << ">" << "\t" << i << '\n';
    os << "]\n";
    return os;
}
ostream& operator<< (ostream& os, Reading& r) {
    os << r.hour << "\t:\t" << r.temperature << " (" << (r.format == Celsius ? "Celsius" : "Fahrenheit") << ")";
    return os;
}