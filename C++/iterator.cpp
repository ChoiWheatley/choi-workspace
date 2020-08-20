#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    /*
    반복자 개념을 포인터로 적용한 예제
    반복자의 조건 : 
    ||| 컨테이너와 컨테이너 안 요소를 구별한다 
    ||| 요소의 값을 확인한다 
    ||| 컨테이너 안에 있는 요소들 간에 이동할 수 있는 연산을 제공한다 
    ||| 컨테이너가 효고적으로 처리할 수 있는 방식으로 가용한 연산들을 한정한다.
    다음의 it 이터레이터는 임의접근 반복자를 만족한다.
    int arr[] = {1, 2, 3, 4, 5};
    int *it;

    for (it = &arr[0]; it != &arr[5]; it++) {
        cout << to_string(*it) + " ";
    }
    cout << endl;
    */
   int arr[] = {1, 2, 3, 4, 5};
   vector<int> vi(arr, arr + 5);
   for (vector<int>::iterator it = vi.begin(); it != vi.end(); it++) {
       cout << to_string(*it) + " ";
   }
   cout << endl;
   
   

    return 0;
}