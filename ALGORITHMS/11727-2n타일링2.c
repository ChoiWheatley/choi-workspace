#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAXN 1001
#define MODULO 10007

int tile(int n);

int main(void)
{
#ifndef DBG
	int input = 0;
	scanf("%d", &input);
	printf("%d\n", tile(input));
    return 0;
#else
    for (int i = 1; i < MAXN; i++) {
        printf("D[%d]=%5d\t", i, tile(i));
        if ( i % 10 == 0 ) 
            puts("");
    }
    return 0;
#endif
}
int tile(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 3;

    int D[MAXN] = {0, 1, 3};
    for (int i = 3; i <= n; i++) {
        D[i] = (  (D[i-1]%MODULO)  + ((D[i-2]%MODULO) * 2) % MODULO  ) % MODULO;
    }
    return D[n];
}
