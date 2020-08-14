/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <ctime>

using namespace std;

int stack_cnt = -1;

void stack_push(char *origin, char w){
    origin[++stack_cnt] = w;
    return;
}
void stack_flush(char *origin){
    char tmp;
    for (int i = 0; tmp != '\0'; i++) {
        tmp = origin[i];
        origin[i] = 0;
    }
    stack_cnt = -1;
    return;
}
int max(int a, int b) {
    if (a < b) { return b; }
    else { return a; }
}
//a[] 에서 b[]를 뺍니다 그 반대도 수행합니다.
void array_mask(int *a_, int *b_) { 
    int a, b, tmp;
    for (int i = 2; i <= 200; i++) {
        a = a_[i];
        b = b_[i];
        if (a > 0 && b > 0) {
            tmp = a - b;
            b = b - a;
            a = tmp;
            if (a < 0) { a = 0; }
            if (b < 0) { b = 0; }
        }
        a_[i] = a;
        b_[i] = b;
    }
}

int multitude(int *arr) {
    int tmp = 1;
    for (int i = 2; i <= 200; i++) {
        if (!arr[i]) { continue; }
        tmp *= pow(i, arr[i]);
    }
    return tmp;
}

int* short_fraction(int a, int b) {
    int x1_[201] = {0}, x2_[201] = {0};
    static int out[2] = {0};
    for (int i = 2; i <= max(a, b); i++) {
        if (!(a % i)) { 
            x1_[i]++; 
            a /= i--;
            continue;
        }
        if (!(b % i)) { 
            x2_[i]++; 
            b /= i--;
            continue;
        }
    }
    array_mask(x1_, x2_);
    out[0] = multitude(x1_);
    out[1] = multitude(x2_);

    return out;
}

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	freopen("input.txt", "r", stdin);

	cin >> T;
    cin.ignore(1);
	for(test_case = 0; test_case  < T; test_case++)
	{

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
        char input_str[17] = {0, };
        char tmp_stack[6] = {0, };
        char tmp_char = ' ';
        int a, b, c; //ax ? b = c;
        int x1, x2;     //x = x1 / x2
        
        cin.getline(input_str, 17);

        for (int i = 0; tmp_char != '\0'; i++) {
            tmp_char = input_str[i];
            if (tmp_char == 'x') {
                a = atoi(tmp_stack);
                stack_flush(tmp_stack);
                continue;
            } else if (tmp_char == '=') {
                b = atoi(tmp_stack);
                stack_flush(tmp_stack);
                continue;
            } else if (tmp_char == ' ') {
                continue;
            } else if (tmp_char == '-') {
                continue;
            }
            stack_push(tmp_stack, tmp_char);
        }
        c = atoi(tmp_stack);
        stack_flush(tmp_stack);
        //cout << "a = " << a << " b = " << b << " c = " << c << endl;

        x1 = b + c;
        x2 = a;
        //cout << x1 << " / " << x2 << "->\t";
        a = x1;
        b = x2;
        x1 = short_fraction(a, b)[0];
        x2 = short_fraction(a, b)[1];
        //cout << x1 << " / " << x2 << endl;


		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << x1 << " / " << x2 << endl;


	}
    /*
    DEBUG
    */
   /*
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < 100; i++) {
        int a = rand();
        int b = rand();
        a = (a % 100) + 1;
        b = (b % 100) + 1;
        cout << a << " / " << b << "\t -> \t";
        cout << short_fraction(a, b)[0] << " / " << short_fraction(a, b)[1] << endl;
    }
    */

	return 0;//Your program should return 0 on normal termination.
}

