/*
    shared memory with file. 
    한 프로세스는 공유메모리를 감시하고, 다른 프로세스는 공유메모리에 값을 작성하는 코드를 구현한다.
*/
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<time.h>
#include<math.h>
#include<CSHutil.h>

/* #define SHARED_FILENAME "shared_file" */     // 이제는 파일을 사용하지 않는다.
#define MAX_BUF 1024

#ifndef MAP_ANONYMOUS
#define MAP_ANONYMOUS 0x20
#endif//MAP_ANONYMOUS

struct login_info 
{
    int pid;
    int counter;
	char message[MAX_BUF];
};

struct login_info* init_login_info();
int do_monitoring(struct login_info* info);
int do_login(int count, struct login_info* info, char message[MAX_BUF]);


int main(int argc, char **argv)
{
    int ret = 0;
    struct login_info* info = init_login_info();
    
    // fork 전에 anoymous mapping을 만들어놓는다.
    if (info == NULL)
    {
        perror("mmap failed");
        return EXIT_FAILURE;
    }

#define NUM_FORK 5
    for (int i = 0; i < NUM_FORK; i++)
    {
        // fork
        pid_t pid = fork();

        if (pid > 0)
        {
            // parent
        }
        else if (pid == 0)
        {
            // child
            char message[MAX_BUF];
            sprintf(message, "hello! from (%d)", i);
            ret = do_login(i, info, message);

            //int munmap(void *addr, size_t length);
            munmap(info, sizeof(struct login_info));

            exit(ret);
        }
        else
        {
            // error case
            perror("fork error");
            exit(EXIT_FAILURE);
        }
    }
    ret = do_monitoring(info);
    wait(NULL);

    //int munmap(void *addr, size_t length);
    munmap(info, sizeof(struct login_info));

    exit(ret);
}

struct login_info* init_login_info()
{
	struct login_info *info;
//        #include <sys/mman.h>
//
//       void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);
//       int munmap(void *addr, size_t length);
//
	
	puts("im mmapping!");
	info = mmap(NULL, sizeof(struct login_info), 
			PROT_READ | PROT_WRITE, 
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	INSPECT( 
            info != MAP_FAILED,
			return NULL;
		   );
    return info;
}

// monitoring 쪽이 파일을 생성한다.
int do_monitoring(struct login_info* info)
{
    // file open | creat
    // mmap
    // init shared memory
    // waiting for change
	struct login_info local;
    const int MAX_TIMEOUT = 50;
    int timeout_count = MAX_TIMEOUT;

    memset(&local, 0, sizeof(struct login_info));
    puts("im waiting for change!!");
	while(timeout_count-- >= 0)
	{
		// int memcmp(const void *s1, const void *s2, size_t n);
		if ( memcmp(info, &local, sizeof(struct login_info)) )
		{
            timeout_count = MAX_TIMEOUT;
			// not same
			printf("[pid, counter, message] = [%d, %d, %s]\n", 
				info->pid, 
                info->counter,
                info->message);
			// local <= info
			memcpy(&local, info, sizeof(struct login_info));
		}

        // 값이 바뀔 때마다가 아니라 0.1초에 한 번씩 모니터링을 수행
        // 강의에서는 client가 index+1 초동안 sleep하는 것으로 수정했지만
        // 나는 시그널을 보내 확인하는 코드를 작성하고 싶다.
		usleep(pow(10,5));
	}


	return 0;
}

int do_login(int count, struct login_info* info, char message[MAX_BUF])
{
    // mmap
    // pid, counter 설정 struct login_info
    sleep(count + 1);

    puts("im writing!!");
    info->pid = getpid();
    info->counter++;
    strncpy(info->message, message, MAX_BUF);


	return 0;
}
