#ifndef CSHUTIL_H
#define CSHUTIL_H

/*
 *  이 헤더파일은 C, C++ 코딩을 하며 즉석으로 제작한 유용한 [ 헬퍼함수 / 매크로 / 오류처리 / IO ]  관련 코드를 아카이빙 합니다. C 스타일 헤더파일이 될 것이고, 만일 C++ 에서만 작동하는 기능이 있다면 c++를 위한 전용 라이브러리를 하나 새로 팔 예정입니다.
 */

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<assert.h>
#define CSH_MAXBUF 1<<12
 
// INSPECT() 매크로 함수는 assert() 매크로의 확장판입니다. __func__, __LINE__, #expr 까지는 동일한데, 에러 핸들링 과정을 추가했습니다.  
// 용법: INSPECT( <expr_a> , <expr_b> )
// expr_a 의 값이 assert의 것과 동일하게 'false'이면  expr_b를 실행합니다.
#define INSPECT(expr, then) \
    if ((expr)==0) {\
        char errmsg[CSH_MAXBUF];\
        fprintf(stderr, "in function `%s()`, line number `%d` ,\n", __func__, __LINE__);\
        sprintf(errmsg, "`%s` has error occured!\n", #expr);\
        perror(errmsg);\
        then\
    }

// round up : 올림 연산을 수행하는 매크로입니다.
// num의 dig 보다 작은 자릿수를 dig로 올리는 작업을 수행합니다.
#define ROUNDUP(num, dig)  ( ((num) + (dig-1)) & ~(dig-1) )


#endif//CSHUTIL_H
