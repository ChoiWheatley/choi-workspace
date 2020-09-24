/*
 * 
 * 
 */

#include "std_lib_facilities.h"

class Bad_area
{
public:
	string name = "bad area";
}; // a type specifically for reporting errors from area()

int f(int,int,int);
int framed_area(int,int);
int area(int, int);




//
//
int main()
{
	try
	{
		int x = 1;
		int y = 2;
		int z = 4;
		int area1 = area(x,y);
		cout << area1 << endl;
		int area2 = framed_area(1,z);
		cout << area2 << endl;
		int area3 = framed_area(y,z);
		cout << area3 << endl;
		double ratio = area1 / area3;
		cout << ratio << endl;
	}
	catch(Bad_area e)
	{
		cout << "Ooops! bad arguments to area()\n" << e.name << endl;;
	}
	
	
	return 0;
}
//
//

int f(int x, int y, int z)
{
	int area1 = area(x,y);
	cout << area1 << endl;
	if (area1 <= 0) error("non-positive area");
	int area2 = framed_area(1,z);
	cout << area2 << endl;
	int area3 = framed_area(y,z);
	cout << area3 << endl;
	double ratio = double(area1) / area3;
	cout << ratio << endl;
	
	return area1;
}
int framed_area(int x, int y)
{
	constexpr int frame_width = 2;
	return area(x - frame_width, x - frame_width);
}
int area(int x, int y)
{
	if (x <= 0 || y <= 0)
	{
		throw Bad_area{};
	}
	return x * y;
}
