/*
수를 이진수로 나타냈을 때, 포함되는 1의 개수를 Population count, 줄여서 popcount라고 부른다. 
자연수 N이 주어졌을 때, N의 popcount를 구하는 프로그램을 작성하시오. 
예를 들어, 13을 이진수로 나타내면 1101이 되며, 13의 popcount는 3이다.

입력 파일에는 여러 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에 테스트 케이스의 개수를 나타내는 자연수 T 가 주어지고,
이후 차례로  T 개의 테스트 케이스가 주어진다. (1 ≤ T ≤ 10,000)
각 테스트 케이스의 입력은 다음과 같은 형식이다.
첫 번째 줄에 자연수 N이 주어진다. (1 ≤ N ≤ 1,000,000,000)

- 점수 : 최대 10회 제출하여 취득한 각각의 점수 중에서 최대 점수 (만점 100점)
모든 테스트 케이스를 맞추었을 때 만점을 받는다.
출력
각 테스트 케이스의 답을 순서대로 표준출력으로 출력하여야 하며,
각 테스트 케이스마다 첫 줄에는 “Case #C”를 출력하여야 한다. 이때 C는 테스트 케이스의 번호이다.
그 다음 줄에 문제의 정답을 출력한다. 주어진 자연수 N을 이진수로 나타내었을 때 포함되는 1의 개수를 출력한다.
입출력예
입력
2
13
15
출력
Case #1
3
Case #2
4
*/

/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <stdio.h>

int Answer = 0;

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
		int a;
		scanf("%d", &a);
		while(a != 0) {
			if (a % 2) {
				Answer++;
			}
			a /= 2;
		}
        		// Print the answer to standard output(screen).
        
		printf("Case #%d\n", test_case+1);
	        	printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}