/*
    shared memory with SysV. 
    한 프로세스는 공유메모리를 감시하고, 다른 프로세스는 공유메모리에 값을 작성하는 코드를 구현한다.
*/
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<time.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/procfs.h> // PAGE_SIZE
#include<CSHutil.h>

#define SHMKEY_FILENAME "/tmp"
#define SHMKEY_PROJID 'r'
#define MAX_BUF 1024

struct login_info 
{
    int pid;
    int counter;
	char message[MAX_BUF];
};

static void print_usage(const char* progname);
int do_monitoring(void);
int do_login(char message[MAX_BUF]);


int main(int argc, char **argv)
{
    int ret;

	if (argc < 2)
	{
		print_usage(argv[0]);
		return -1;
	}
    if (!strcmp(argv[1], "monitor")) 
    {
        ret = do_monitoring();
    }
	else if (argc > 2 && !strcmp(argv[1], "sender"))
	{
        ret = do_login(argv[2]);
	}
    else
    {
		print_usage(argv[0]);
		return -1;
    }
    return ret;
}

static void print_usage(const char* progname)
{
    fprintf(stderr, "%s <monitor | sender <message> >\n", progname);
}

/* #define ROUNDUP(num, dig)  ( ((num) + (dig-1)) & (dig-1) ) */
// monitoring 쪽이 파일을 생성한다.
int do_monitoring(void)
{
    // 1. init shared memory (ftok -> shmget -> shmat)
    // 2. waiting for change
    // 3. detach shm and remove shm_id (shmdt, shmctl)
	struct login_info *info;
	struct login_info local;
    size_t size;
    key_t key;
    int shm_id;


/* #include <sys/ipc.h> */
/* #include <sys/shm.h> */
/* int shmget(key_t key, size_t size, int shmflg); */
/* - size: 페이지 사이즈의 배수로 제공 */
/* key_t ftok(const char *pathname, int proj_id); */
    puts("im creating key and shared memory!!");
    key = ftok(SHMKEY_FILENAME, SHMKEY_PROJID);
    INSPECT(key != -1,
            return -1;
           );
    size = sizeof(struct login_info);

    size = ROUNDUP(size, PAGE_SIZE);
    shm_id = shmget(key, size, 0644 | IPC_CREAT);
    INSPECT(shm_id != -1,
            return -1;
           );


/* void *shmat(int shmid, const void *shmaddr, int shmflg); */ 
    puts("im attaching shared memory!");
    info = (struct login_info*)shmat(shm_id, NULL, 0);
    INSPECT(info != (void*)-1,
            return -1;
           );
    memset(info, 0, sizeof(struct login_info));

    
    puts("im waiting for a change!!");
    memset(&local, 0, sizeof(struct login_info));
	while(strncmp(local.message, "exit", 5))
	{
		// int memcmp(const void *s1, const void *s2, size_t n);
		if ( memcmp(info, &local, sizeof(struct login_info)) )
		{
			// not same
			printf("[pid, counter, message] = [%d, %d, %s]\n", 
				info->pid, 
                info->counter,
                info->message);
			// local <= info
			memcpy(&local, info, sizeof(struct login_info));
		}
		sleep(1);
	}

/* int shmdt(const void *shmaddr); */
    puts("im detaching shared memory and closing shared id!!");
    shmdt(info);
    shmctl(shm_id, IPC_RMID, NULL);
	return 0;
}

int do_login(char message[MAX_BUF])
{

    // 1. init shared memory (ftok, shmget, shmat)
    // 2. write to shared memory
    // 3. detach shared memory
	struct login_info *info;
    size_t size;
    key_t key;
    int shm_id;


/* #include <sys/ipc.h> */
/* #include <sys/shm.h> */
/* int shmget(key_t key, size_t size, int shmflg); */
/* - size: 페이지 사이즈의 배수로 제공 */
/* key_t ftok(const char *pathname, int proj_id); */
    puts("im creating key and shared memory!!");
    key = ftok(SHMKEY_FILENAME, SHMKEY_PROJID);
    INSPECT(key != -1,
            return -1;
           );
    size = sizeof(struct login_info);
    size = ROUNDUP(size, 4096);
    shm_id = shmget(key, size, 0644);
    INSPECT(shm_id != -1,
            return -1;
           );


/* void *shmat(int shmid, const void *shmaddr, int shmflg); */ 
    puts("im attaching shared memory!");
    info = (struct login_info*)shmat(shm_id, NULL, 0);
    INSPECT(info != (void*)-1,
            return -1;
           );


    printf("prev info[pid,counter,msg]=[%u, %d, %s]\n", 
        info->pid, 
        info->counter,
        info->message);
    /* memset(info, 0, sizeof(struct login_info)); */


    puts("im writing to shared memory!!");
    info->pid = getpid();
    info->counter+=1;
    strncpy(info->message, message, MAX_BUF);

    puts("im detaching shared memory!!");
    shmdt(info);

	return 0;
}
