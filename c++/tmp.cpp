/*
 * 
 * 20200915 4_Ex4 Program Which Guesses a Number
 * 
 * Write a program to play numbers guessing game
 * The user thinks of a number between 1 and 100
 * and your PROGRAM asks questions to figure out
 * what the number is 
 * (e.g., "Is the number you are thinking of less
 * than 50?")
 * Your program should be able to identify the number
 * after askingno more than seven questions.
 * 
 */

#include "std_lib_facilities.h"


int main()
{
	int guess = 50, left = 1, right = 100;
	char answer = 0;
	for (int i = 0; i < 7; i++)
	{
		cout << "Is the number you are thinking is "<< guess <<"? (answer with >, <, =)" << endl;
		cin >> answer;
		if (answer == '>')
		{
			right = guess;
			guess = (left + guess) / 2;
		} else if (answer == '<')
		{
			left = guess;
			guess = (right + guess) / 2;
		} else if (answer == '=')
		{
			cout << "CORRECT! the answer is " << guess << endl;
			break;
		} else
		{
			cout << "I cannot sure you wrote an adequate answer.\n";
			i--;
			continue;
		}
	}
	cout << "Ooops..." << endl;
	return 0;
}

