/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>

using namespace std;

char Answer[10] = {0};
const char Alice[10] = "Alice";
const char Bob[10] = "Bob";
const char Playing[10] = "Playing";

void str_init(char *, int);
// a <- b
void str_change(char *a, const char *b, int size);	
void str_change(char *a, char *b, int size);	

void str_init(char *a, int size) {
	for (int i = 0; i < size; i++) {
		a[i] = 0;
	}
	return;
}
void str_change(char *a, const char *b, int size) {
	for (int i = 0; i < size; i++) {
		a[i] = b[i];
	}
	return;
}
void str_change(char *a, char *b, int size) {
	for (int i = 0; i < size; i++) {
		a[i] = b[i];
	}
	return;
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

	 //freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		str_init(Answer, 10);
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		char case_str[42] = {0};
		char case_char = 1;
		int alice_point = 0;
		int bob_point = 0;

		cin >> case_str;
		for (int i = 0; i < 42 || !case_char; i++) {
			case_char = case_str[i];
			if (case_char == 'A') { alice_point++; }
			else if (case_char == 'B') { bob_point++; }
			if (alice_point >= 21) { 
				str_change(Answer, Alice, 6);
				break;
			}
			else if (bob_point >= 21) { 
				str_change(Answer, Bob, 4);
				break;
			}
		}
		if (!Answer[0]) {
			str_change(Answer, Playing, 8);
		}
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}