#include "std_lib_facilities.h"
using namespace std;

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


int main(void) 
{
    vector<Point> original_points;
    for (int i = 0; i < 7; i++) {
        original_points.push_back(prompt_point());
    }
    cout << original_points;

    ofstream os{"mydata.txt"};
    if (!os) error("cannot open file. please check if the file names isn't correct");
    os << original_points;
    

    return 0;
}

ostream& operator<<(ostream& os, Point& p) {
    os << "[" << p.x << ", " << p.y << "]\n";
    return os;
}
ostream& operator<<(ostream& os, vector<Point>& p) {
    for (auto i : p) os << i;
    return os;
}