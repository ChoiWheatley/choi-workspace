/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <stdio.h>
#include <stdlib.h>

int Answer;

int main(void)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using scanf function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */
	//freopen("input.txt", "r", stdin);

	/*
	   If you remove the statement below, your program's output may not be recorded
	   when your program is terminated after the time limit.
	   For safety, please use setbuf(stdout, NULL); statement.
	 */
	setbuf(stdout, NULL);

	scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		
		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = 0;
		
		int A, B, *numPtr;
		scanf("%d %d", &A, &B);
		numPtr = malloc(sizeof(int) * B + 1);
		for (int i = 0; i <= B; i++){
			numPtr[i] = 0;
		}
		numPtr[0] = 0;
		numPtr[1] = B - A + 1;
		for(int i = 2; i <= B; i++) {
			for (int j = A; j <= B; j++) {
				if (!(j % i)) {
					numPtr[i]++;
				}
			}
		}
		//printf("test:\nA: %d B: %d\n", A, B);
		for (int i = 1; i <= B; i++) {
		//	printf("%d : %dea\n", i, numPtr[i]);
			Answer += i * numPtr[i];
		}

		free(numPtr);
        		// Print the answer to standard output(screen).
		printf("Case #%d\n", test_case+1);
	        	printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}
