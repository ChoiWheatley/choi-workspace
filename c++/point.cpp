#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>

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

void print_point(vector<Point>& p) {
    for (auto i : p) cout << "[" << i.x << ", " << i.y << "]\n";
}

int main(void) 
{
    vector<Point> original_points;
    for (int i = 0; i < 7; i++) {
        original_points.push_back(prompt_point());
    }
    print_point(original_points);

    return 0;
}