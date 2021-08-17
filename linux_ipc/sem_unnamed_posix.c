/*
 * shared memory with POSIX api
 * shm 생성 -> mmap
 * shm -> semaphore
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
#include<semaphore.h>
#include"../util/CSHutil.h"

#define SHARED_FILENAME "/semaphore"
#define MAX_BUF 1024

struct login_info 
{
    int pid;
    int counter;
    sem_t sem;
};

static void print_usage(const char* progname);
int do_monitoring(void);
int do_login(void);
int do_logout(void);


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		print_usage(argv[0]);
		return -1;
	}
    if (!strcmp(argv[1], "monitor")) 
    {
        do_monitoring();
    }
	else if (!strcmp(argv[1], "get"))
	{
        do_login();
	}
	else if (!strcmp(argv[1], "put"))
	{
        do_logout();
	}
    else
    {
		print_usage(argv[0]);
		return -1;
    }

    return 0;
}

static void print_usage(const char* progname)
{
    fprintf(stderr, "%s <monitor | get | put> \n", progname);
}

// monitoring 쪽이 파일을 생성한다.
int do_monitoring(void)
{
    // file open | creat
    // mmap
    // init shared memory
    // waiting for change
    int fd;
    int sem_val;
	struct login_info *info;
	struct login_info local;


/* #include <sys/mman.h> */
/* #include <sys/stat.h>        /1* For mode constants *1/ */
/* #include <fcntl.h>           /1* For O_* constants *1/ */
/* int shm_open(const char *name, int oflag, mode_t mode); */
/* int shm_unlink(const char *name); */
/* Link with -lrt. */
    char debugstr[MAX_BUF];
    sprintf(debugstr, "in pid: %d, opening a posix shared memory!", getpid());
    puts(debugstr);

    fd = shm_open(SHARED_FILENAME, O_RDWR | O_CREAT, 0644);
	INSPECT( 
			fd != -1,
			return -1;
		   );
	

	puts("im truncating file size!");
	INSPECT(
			ftruncate(fd, sizeof(struct login_info)) != -1,
			return -1;
		   );


//        #include <sys/mman.h>
//
//       void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);
//       int munmap(void *addr, size_t length);
//
	
	puts("im mmapping!");
	info = mmap(NULL, sizeof(struct login_info), 
			PROT_READ | PROT_WRITE, 
			MAP_SHARED, fd, 0);
	INSPECT( info != MAP_FAILED,
			close(fd);
			return -1;
		   );
    memset(info, 0, sizeof(struct login_info));


    // making semaphore
    puts("im making semaphore!");
    INSPECT(sem_init(&info->sem, 1, 3) != -1,
            return -1;);

    close(fd);
	
    memset(&local, 0, sizeof(struct login_info));
    puts("im waiting for change!!");
	while(local.counter <= 15)
	{
		// int memcmp(const void *s1, const void *s2, size_t n);
		if ( memcmp(info, &local, sizeof(struct login_info)) )
		{
			// not same
            /* int sem_getvalue(sem_t *sem, int *sval); */
            sem_getvalue(&info->sem, &sem_val);
			printf("[pid, counter, sem] = [%d, %d, %d]\n", 
				info->pid, 
                info->counter,
                sem_val);
			// local <= info
			memcpy(&local, info, sizeof(struct login_info));
		}
		sleep(1);
	}

    puts("im destroying a semaphore!");
    sem_destroy(&info->sem);

	//int munmap(void *addr, size_t length);
	munmap(info, sizeof(struct login_info));
/* int shm_unlink(const char *name); */
	/* shm_unlink(SHARED_FILENAME); */
	close(fd);

	return 0;
}

int do_login(void)
{
    // 1. mmap
    // 2. semaphore initialize
    // 3. pid, counter 설정 struct login_info

    int fd;
	struct login_info *info;


/* #include <sys/mman.h> */
/* #include <sys/stat.h>        /1* For mode constants *1/ */
/* #include <fcntl.h>           /1* For O_* constants *1/ */
/* int shm_open(const char *name, int oflag, mode_t mode); */
/* int shm_unlink(const char *name); */
/* Link with -lrt. */
	puts("im opening");
    INSPECT( (fd = shm_open(SHARED_FILENAME, O_RDWR | O_EXCL, 0644)) != -1,
            return -1;
           );

//        #include <sys/mman.h>
//
//       void *mmap(void *addr, size_t length, int prot, int flags,
//                  int fd, off_t offset);
//       int munmap(void *addr, size_t length);
//
	puts("im mmapping!");
	info = mmap(NULL, sizeof(struct login_info), 
			PROT_READ | PROT_WRITE, 
			MAP_SHARED, fd, 0);
	INSPECT( info != MAP_FAILED,
			close(fd);
			return -1;
		   );
	close(fd);


    puts("im locking a semaphore!");
    sem_wait(&info->sem); // lock


    info->pid = getpid();
    info->counter++;
    // where is unlock? -> do_logout()


	//int munmap(void *addr, size_t length);
	munmap(info, sizeof(struct login_info));

	return 0;
}

// unlocking semaphore
int do_logout(void)
{
    int fd;
    struct login_info *info;

    puts("im opening!");
    fd = shm_open(SHARED_FILENAME, O_RDWR, 0644);
    INSPECT(fd != -1,
            return -1;);


    puts("im mmaping!!");
    info = mmap(NULL, sizeof(struct login_info),
                PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    INSPECT(info != MAP_FAILED,
            close(fd);
            return -1;);
    close(fd);

    puts("im unlocking a semaphore!");
    sem_post(&info->sem);

    munmap(info, sizeof(struct login_info));

    return 0;
}
