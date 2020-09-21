/*
 * 
 * 
 */

#include <bitset>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	bitset<10> bit;

	// 비트를 모두 0으로 설정
	bit.reset();
	cout << bit << endl;

	// 비트셋으로 선언한 bit의 할당된 수를 구한다.
	cout << bit.size() << endl;

	//비트를 모두 1로 설정
	bit.set();
	cout << bit << endl;

	// 비트셋 중 하나라도 1이면 1을 반환, 모두 0이면 0을 반환한다.
	cout << "return 1 if ANY bit is 1\n" << bit.any() << endl;

	//비트셋 중 하나라도 1이면 0을 반환, 모두 0이면 1을 반환. (!bit.any())
	cout << "return 0 if NONE bit is 0\n" << bit.none() << endl;

	// 다섯번째 비트를 뒤집는다
	bit.flip(4);
	cout << "다섯번째 비트를 뒤집는다 : " << bit << endl;

	// 비트를 string으로 변환
	cout << "비트를 string으로 변환 " << bit.to_string() << endl;




	return 0;
}

