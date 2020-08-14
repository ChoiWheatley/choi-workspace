
#include <iostream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dis(0, 999);
    int *num_ptr;
    int arr_size = 0;

    cin >> arr_size;
    num_ptr = new int[arr_size];
    for (int i = 0; i < arr_size; i++) {
        if (!(i % 30)) { cout << '\n'; }
        num_ptr[i] = dis(gen);
        cout << num_ptr[i] << ' ';
    }    
    cout << endl;
    delete[] num_ptr;

    return 0;
}