#include<semaphore.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/time.h>
#include <time.h>
#include"../util/CSHutil.h"

#define SEM_ID "/test_sem_id"
extern int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

static void print_usage(const char * progname)
{
    fprintf(stderr, "usage: %s <option>\n", progname);
    fprintf(stderr, "option:\n");
    fprintf(stderr, "\
    show                # show current semaphore set status\n\
    | wait              # decrements  (locks) the semaphore pointed to by sem.\n\
    | trywait           # if the  decrement  cannot be immediately performed, then call returns an error instead of blocking.\n\
    | timedwait [sec]   # limit on the amount of time that the call should block if the decrement cannot be immediately performed.\n\
    | release           # release semaphore with index\n\
    \n");
}

static sem_t* init_semaphore(void);
static int show(sem_t *sem);
static int release(sem_t *sem);
static int wait	  (sem_t *sem);
static int trywait(sem_t *sem);
static int timedwait(sem_t *sem, int time_sec);

int main(int argc, char ** argv)
{
	sem_t *sem_id;
    int ret;

    INSPECT((sem_id = init_semaphore()) != NULL,
            return EXIT_FAILURE;)
    
    if (argc < 2) goto err;

    else if (!strcmp(argv[1], "show")) {
        ret = show(sem_id);
    } 
    else if (!strcmp(argv[1], "wait")) {
        ret = wait(sem_id);
    } 
    else if (!strcmp(argv[1], "trywait")) {
        ret = trywait(sem_id);
    } 
    else if (!strcmp(argv[1], "timedwait")) {
		if (argc<3) goto err;
		int time_sec = atoi(argv[2]);
        ret = timedwait(sem_id, time_sec);
    } 
    else if (!strcmp(argv[1], "release")) {
        ret = release(sem_id);
    } 
    else {
        goto err;
    }


    return ret;

err:
    print_usage(argv[0]);
    return EXIT_FAILURE;
}

static sem_t* init_semaphore(void)
{
/* sem_t *sem_open(const char *name, int oflag); */
/* sem_t *sem_open(const char *name, int oflag, */
/*                 mode_t mode, unsigned int value); */
/* Link with -pthread. */
	sem_t *sem;

    INSPECT (
			(sem = sem_open(SEM_ID, O_CREAT, 0644, 3)) != SEM_FAILED,
			return NULL;
			);
    
    return sem;
}

static int show(sem_t *sem)
{
    int i;

	//int sem_getvalue(sem_t *sem, int *sval);
	INSPECT(sem_getvalue(sem, &i) != -1,
			return -1;);
	fprintf(stderr, "semaphore = %d\n", i);

    return 0;
}
static int release(sem_t *sem)
{
	return sem_post(sem);
}
static int wait(sem_t *sem)
{
//int sem_wait(sem_t *sem);
	return sem_wait(sem);
}
static int trywait(sem_t *sem)
{
/* int sem_trywait(sem_t *sem); */

	return sem_trywait(sem);
}
static int timedwait(sem_t *sem, int time_sec)
{
/* int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout); */
/* int clock_gettime(clockid_t clk_id, struct timespec *tp); */
// sem_timedwait 함수는 epoch 이후의 절대시간을 기준으로 대기를 수행한다.
// 따라서 별 생각없이 '3'초 값을 넣어도 이미 지난 시간이기 때문에 바로 
// 리턴을 수행하게 된다. 따라서 현재 시간을 구하여 원하는 만큼 더한 뒤, 
// 그 값을 sem_timedwait() 에 파라메터로 넘겨주어야 한다.
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	t.tv_sec += (time_t)time_sec;
	t.tv_nsec = 0;

	return sem_timedwait(sem, &t);
}
