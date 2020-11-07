/*
 * constexpr funcitons
 * 똑같은 단순연산을 수백만번 수행해야 하는 경우, 컴파일 타임에 미리 연산작업을 굳혀놓을 수 있게 만들어준다.
 */

#include "std_lib_facilities.h"
typedef struct Point {
	double x;
	double y;
} Point;

constexpr double x = 10;
constexpr double y = 0.8;

constexpr Point scale(Point p) {return Point {p.x * x, p.y * y};}
void use(Point p1) {
	constexpr Point p2 {10, 10};
	Point p3 = scale(p1);
	// constexpr Point p4 = scale(p1); // error : p1이 constexpr가 아니라고 오류를 내뱉는다.
	Point p5 = scale(p2);
	constexpr Point p6 = scale(p2);

	cout << p1.x << " | " << p1.y << '\n';
	cout << p2.x << " | " << p2.y << '\n';
	cout << p3.x << " | " << p3.y << '\n';
	cout << p5.x << " | " << p5.y << '\n';
	cout << p6.x << " | " << p6.y << '\n';
}
//
//
int main()
{
	double x, y;
	cin >> x >> y;
	use(Point{x, y});
	return 0;
}
//
//
