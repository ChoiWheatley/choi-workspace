#include <iostream>
#include <cmath>
using namespace std;

class Rect;

class Display
{
public:
	void ShowSize(const Rect & target);
	void ShowDiagonal(const Rect & target);
};

class Rect 
{
private:
	double height_;
	double width_;
public:
	Rect(double h, double w);
	void height() const;
	void width() const;
	friend void Display::ShowDiagonal(const Rect & target);	//프렌드 멤버함수 선언
};

int main() 
{
	Rect rect1(10, 20);
	Display rect_display;	
	rect_display.ShowSize(rect1);
	rect_display.ShowDiagonal(rect1);

	return 0;
}
/*
 * class Rect 구현부
 */
Rect::Rect(double h, double w)
{
	height_ = h;
	width_ = w;
}
void Rect::height() const
{ 
	cout << "높이 : " << this->height_ << endl;
}
void Rect::width() const
{
	cout << "너비 : " << this->width_ << endl;
}



/*
 * class Display 구현부
 */
void Display::ShowSize(const Rect & target)			//일반 멤버함수 : 직접 접근이 불가해 getter 함수 사용
{
	target.height();
	target.width();
}
void Display::ShowDiagonal(const Rect & target)		//Rect의 friend function
{
	double diagonal;
	diagonal = sqrt(pow(target.height_, 2) + pow(target.width_, 2));
	cout << "이 사각형의 대각선 길이는 : " << diagonal << " 입니다." << endl;
}
