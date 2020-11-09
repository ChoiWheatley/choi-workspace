/*
 * Ch8 Drill2
 * 
 * Write three functions swap_v(int,int), swap_r(int&,int&), 
 * and swap_cr(const int&, const int&). Each should have the body 
 * { int temp; temp = a, a=b; b=temp; }
 * 
 */

#include "std_lib_facilities.h"

void swap_v(int, int);
void swap_r(int&, int&);
//void swap_cr(const int&, const int&);
void print(int, int);

//
//
int main()
{
	int x = 7, y = 9;
	print (x, y);
	swap_v(x, y);
	print (x, y);
	swap_r(x, y);
	print (x, y);
	
	return 0;
}
//
//

void swap_v(int a, int b)
{
	int tmp; tmp = a, a = b; b = tmp;
	cout << "in swap_v, ";
	print(a, b);
}
void swap_r(int& a, int& b)
{
	int tmp; tmp = a, a = b; b = tmp;
	cout << "in swap_r, ";
	print(a, b);
}
/*
void swap_cr(const int& a, const int& b)
{
	int tmp; tmp = a, a = b; b = tmp;
	cout << "in swap_cr, ";
	print(a, b);
}
*/
void print(int x, int y)
{
	cout << "x : " << x << " / y : " << y << '\n';
}