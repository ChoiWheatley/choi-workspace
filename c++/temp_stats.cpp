/*
 * PPPUC++ Chapter10 Exercise 3
 * Write a program that reads the data from "raw_temps.txt" created in Ex2 into 
 * a vector and then calculates the mean and median temperatures in your data set.
 * Call the program "temp_stats.cpp"
 * 
 * Thinking
 * - 
 * 
 * Idea
 * ㅁ 메모리 통째로 파일에 옮겨넣을 수는 없는걸까? 
 */

struct Reading{
    int hour;
    double temperature;
};


#include "std_lib_facilities.h"
#include <unistd.h>

vector<Reading> get_readings(ifstream&);
bool skip(ifstream&);
double mean(vector<double>&);
double median(vector<double>&);
vector<double>& get_temperature(vector<Reading>&);
istream& operator>> (istream& is, Reading& r);
ostream& operator<< (ostream& os, vector<Reading>& r);
ostream& operator<< (ostream& os, Reading& r);

int main(void) {
    vector<Reading> readings;
    ifstream ifs{"raw_temps.txt"};
    if (!ifs) error("something wrong with opening the file");
    readings = get_readings(ifs);
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
        //cout << "Debug : " << r << endl;

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
istream& operator>> (istream& is, Reading& r) {
    int hr;
    double temp;
    is >> hr >> temp;
    r.hour = hr;
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
    os << r.hour << "\t:\t" << r.temperature;
    return os;
}