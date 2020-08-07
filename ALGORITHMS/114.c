/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

/*
<114: 근로시간>
어떤 사람의 하루 출근 시각과 퇴근 시각이 주어졌을 때, 근로 시간을 구하는 프로그램을 작성하시오. 
단, 점심 시간이나 휴게 시간은 근무 시간에서 공제하지 않으며, 자정을 넘어간 야근을 한 경우는 없다.

<입력>
입력 파일에는 여러 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에 테스트 케이스의 개수를 나타내는 자연수 T 가 주어지고,
이후 차례로  T 개의 테스트 케이스가 주어진다. (1 ≤ T ≤ 20)
각 테스트 케이스의 입력은 다음과 같은 형식이다.
첫 번째 줄에 출근 시각과 퇴근 시각이 각각 “hh:mm”의 형태로 공백으로 구분되어 주어진다. 
입력으로 존재하지 않는 시각이 주어지지 않으며, 출근 시각이 퇴근 시각보다 늦은 경우도 주어지지 않는다.

<출력>
각 테스트 케이스의 답을 순서대로 표준출력으로 출력하여야 하며,
각 테스트 케이스마다 첫 줄에는 “Case #C”를 출력하여야 한다. 이때 C는 테스트 케이스의 번호이다.
그 다음 줄에 문제의 정답을 출력한다. 한 사람의 근로 시간을 “hh:mm”의 형태로 출력한다.

<입력예>
2
09:00 18:00
09:10 18:03

<출력예>
Case #1
09:00
Case #2
08:53
*/

#include <stdio.h>

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
	// freopen("input.txt", "r", stdin);

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
	
        		// Print the answer to standard output(screen).
        
		printf("Case #%d\n", test_case+1);
	        	printf("%d\n", Answer);
        
	}

	return 0;//Your program should return 0 on normal termination.
}