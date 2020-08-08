/*
일직선 상에 돌들이 놓여있고, 개구리가 처음에는 '좌표 0'에 위치한 돌 위에 앉아 있다.
'좌표 0'에는 돌이 항상 놓여 있고, 모든 돌들은 정수 좌표에 놓여 있다.
개구리는 점프를 통해서 돌들 사이를 이동해서 마지막 돌까지 이동해야 한다.
이 때, 개구리가 한번의 점프로 이동 가능한 최대 거리 K 가 주어진다.
개구리는 한번의 점프로 자신이 앉아 있던 돌에서  K 이하의 거리에 위치한 돌들 중 하나의 돌로 이동 할 수 있다. 
여기서 문제는, '좌표 0'에 위치한 개구리가 마지막 돌까지 이동할 수 있다면,
마지막 돌까지 이동하기 위한 최소 점프 횟수를 계산하는 것이다. 

예를 들어서, 위의 "그림1"의 예에서 보면, 한번의 점프로 이동 가능한 최대 거리가 K=4 로 주어질 때,
아래 "그림2"에서와 같이 5회의 점프로 마지막 돌로 이동할 수 있고, 이것이 최소의 점프 횟수이다. 
또한 위의 예에서, K=2 로 주어진다면 개구리는 마지막 돌로 이동할 수가 없다.
왜냐하면, 개구리가 '좌표 2'의 돌로 이동한 후 '좌표 5'이상의 돌로는 이동할 수 없기 때문이다. 

입력 파일에는 여 개의 테스트 케이스가 포함될 수 있다.
파일의 첫째 줄에는 테스트 케이스 개수를 나타내는 자연수 T가 주어지고,
이후 차례로 T개의 테스트 케이스가 주어진다. ( 1≤T≤5 ) 
각각의 테스트 케이스 첫 번째 줄에는 '좌표 0'에 놓인 돌을 제외한 나머지 돌들의 개수 N 이 주어진다. ( 1≤N≤1,000,000 )
두 번째 줄에는 돌들이놓인 좌표를 나타내는 N 개의 정수 ai들이 빈칸(공백)을 사이에 두고 주어진다. (1≤ai≤109 )
여기서, 주어진 좌표들은 증가하는 순서로 주어지고 모두 다르다.
세 번째 줄에는 개구리가 한 번의 점프로 이동 가능한 최대 거리 K 가 주어진다. ( 1≤K≤109 )

출력
각 테스트 케이스의 답을 순서대로 표준출력으로 출력하여야 하며, 각 테스트 케이스마다 첫 줄에 “Case #T”를 출력하여야 한다.
이때 T는 테스트 케이스의 번호이다.
그 다음 줄에는 개구리가 지막 돌로 이동할 수 있는 최소 점프 횟수를 출력한다.
만약, 개구리가 마지막 돌로 이동하는 것이 불가능한 경우에는 "-1"을 출력한다.

입출력예
입력
3
8
1 2 5 7 9 10 12 15
4
8
1 2 5 7 9 10 12 15
2
17
3 4 8 10 14 18 20 22 23 25 30 33 34 36 38 39 42
7
출력
Case #1
5
Case #2
-1
Case #3
8
*/
/*
You hould use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <stdio.h>
#include <stdbool.h>

void arrInit(int *a);
int Answer;
int a[1000001] = {0};


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
	freopen("input.txt", "r", stdin);

	/*
	   If you remove the statement below, your program's output may not be rocorded
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
		int n, k;
		int now = 0;
		int count = 0;
		bool jumpable = true;
		arrInit(a);
		
		scanf("%d", &n);
		for (int i = 1; i <= n; i++){
			scanf("%d ", a + i);
		}
		scanf("%d", &k);

		/*debug//////////////////////////////////////////////
		printf("n = %d, k = %d, *a = [", n, k); 			//
		for (int i = 0; i <= n; i++){						//
			printf("%d ", *(a + i));						//
		}													//
		printf("\b]\n");									//
		//debug*//////////////////////////////////////////////

		for (int i = 0; i < n - 1; i++) {
			if (a[i + 1] - a[i] > k) { //k보다 돌 사이의 거리가 크면 이동할 수 없다.
				count = -1;
				jumpable = false;
			}
		}
		while (now != a[n] && jumpable) {
			for (int i = n; i > 0; i--) {
				if (a[i] <= now + k) {
					now = a[i];
					//printf("now = %d\n", now);
					count++;
					i = n;
					break;
				}
			}
		}
		Answer = count;

	
        // Print the answer to standard output(screen).
        
		printf("Case #%d\n", test_case+1);
        printf("%d\n", Answer);
	}

	return 0;//Your program should return 0 on normal termination.
}

void arrInit(int *a) {
	int out[1000001] = {0};
	a = out;
}