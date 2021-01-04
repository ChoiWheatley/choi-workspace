#include "std_lib_facilities.h"
#include <unistd.h>

struct Point {
    int x;
    int y;
};

Point prompt_point() {
    int x, y;
    cout << "Please input two integers with whitespace\n>>";
    cin >> x >> y;
    return *(new Point{x, y});
}

ostream& operator<<(ostream& os, Point& p);
ostream& operator<<(ostream& os, vector<Point>& p);
istream& operator>>(istream& is, Point& p);
istream& operator>>(istream& is, vector<Point>& p);



int main(void) 
{
    vector<Point> original_points;
    vector<Point> processed_points;
    for (int i = 0; i < 7; i++) {
        original_points.push_back(prompt_point());
    }
    cout << original_points;

    // Drill4. Open an ofstream and output each point to a file
    ofstream os;
    os.open("mydata.txt");
    if (!os) error("cannot open file. please check if the file names isn't correct");
    os << original_points;
    os.close();

    // Drill5. Close the ofstream and then open an ifstream for "mydata.txt"
    ifstream is;
    is.open("mydata.txt");
    if (!is) error("cannot open file. please check if the file names isn't correct");
    // get points from is
    is >> processed_points;
    cout << processed_points;


    return 0;
}

ostream& operator<<(ostream& os, Point& p) {
    os << p.x << " " << p.y << "\n";
    return os;
}
ostream& operator<<(ostream& os, vector<Point>& p) {
    for (auto i : p) os << i;
    return os;
}
istream& operator>>(istream& is, Point& p) {
    int x, y;
    is >> x >> y;
    p = Point{x, y};
    return is;
}
// 동작안함 
istream& operator>>(istream& is, vector<Point>& p) {
    is.exceptions(is.exceptions() | ios_base::badbit);
    for (Point pnt; true; ) {
        is >> pnt;
        //cout << (is.good() ? "good, " : is.eof() ? "eof, " : is.fail() ? "fail " : "bad ");
        if (is.good())
            p.push_back(pnt);
        if (is.eof()) 
            return is;
        if (is.fail()) { // format error
            is.clear();
            char ch;
            for (ch = is.get(); (is && ch != '\n') ; ch = is.get()) {
                /* do nothing */
            }
            if (!is) error("somthing wrong with istream");
            is.unget();
        }
    }
    
    return is;
}