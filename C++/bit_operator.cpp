#include <cstdio>
#include <iostream>
using namespace std;

int * bit_reverse(int *arr, int arr_size);
int * bit_disintegration(int a, int type_size);
char * arr_to_str(int* arr, int arr_size);

int * bit_reverse(int *arr, int arr_size) {
    int *out = (int *)calloc(arr_size, sizeof(int));
    for (int i = 0; i < arr_size; i++) {
        out[i] = arr[arr_size - 1 - i];
    }
    free(arr);
    return out;
}

int * bit_disintegration(int a, int type_size) {
    const int mask = 1;
    const int arr_size = type_size * 8;
    int *arr_bit = (int *)calloc(arr_size, sizeof(int));
    
    for (int i = 0; i < arr_size; i++) {
        arr_bit[i] = a & mask;
        a = a >> 1;
    }
    return bit_reverse(arr_bit, arr_size);
}

char * arr_to_str(int* arr, int type_size) {
    const int arr_size = (type_size * 8);
    char *out = (char *)calloc(arr_size, sizeof(char));
    for (int i = 0; i < arr_size; i++) {
        out[i] = arr[i] + 48;
    }
    free(arr);
    return out;
}



int main() {
    int num = 15;
    int arr[5] = {0, 1, 2, 3, 4};
    cout << "~15 = " << (~num) << " 입니다." << endl;
    cout << "~(~15) = " << ~(~num) << " 입니다." << endl;

    cout << "15의 비트는 " << arr_to_str(bit_disintegration(num, sizeof(int)), sizeof(int)) << " 입니다." << endl;
    cout << "~15의 비트는 " << arr_to_str(bit_disintegration(~num, sizeof(int)), sizeof(int)) << " 입니다." << endl;


    return 0;
}