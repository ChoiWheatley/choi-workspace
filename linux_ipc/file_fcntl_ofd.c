#define _GNU_SOURCE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

#include"../util/CSHutil.h"

static inline int open_file(void);

#define FILESIZ             1024
#define NUM_SECTION         4
#define SECTION_SIZ         (FILESIZ) / (NUM_SECTION)
#define LOCK_FILENAME       ".fcntl_lockfile"


static void print_usage(const char *progname)
{
	printf("usage: %s [rd|wr] [section number]\n", progname);
}

int main(int argc, char ** argv)
{
    // open file
    // fcntl() :: advisory record locking
        // cmd : record lock
        // struct flock
        // 파일의 영역을 나누어 lock section으로 사용한다.
    int fd, section_no;
	struct flock locker;

	if (argc < 3) {
		goto err;
	}


	// CAVEAT: 
	// atoi() 함수는 에러처리를 안한다. undefined behavior
	section_no = strtol(argv[2], NULL, 10);
	memset(&locker, 0, sizeof(struct flock));
	if (!strcmp(argv[1], "rd")) {
		locker.l_type = F_RDLCK;
	} else if (!strcmp(argv[1], "wr")) {
		locker.l_type = F_WRLCK;
	} else {
		goto err;
	}


    puts("im opening a file!");
    fd = open_file();
    INSPECT(fd!=-1, return -1;);


    
    puts("im truncating a file!");
    INSPECT(ftruncate(fd, FILESIZ) != -1, return -1;);

	/* int fcntl(int fd, int cmd, ... /1* arg *1/ ); */
    /*F_SETLK, F_SETLKW, and F_GETLK are used to acquire, release, and test for the  existence  of  record  locks (also known as byte-range, file-segment, or file-region locks).  The third argument, lock, is a pointer to a structure that has  at  least the following fields (in unspecified order). 
	 * When placing locks with F_SETLKW, the kernel detects  deadlocks
	*/
    /*        struct flock { */
    /*            ... */
    /*            short l_type;    /1* Type of lock: F_RDLCK, */
    /*                                F_WRLCK, F_UNLCK *1/ */
    /*            short l_whence;  /1* How to interpret l_start: */
    /*                                SEEK_SET, SEEK_CUR, SEEK_END *1/ */
    /*            off_t l_start;   /1* Starting offset for lock *1/ */
    /*            off_t l_len;     /1* Number of bytes to lock *1/ */
    /*            pid_t l_pid;     /1* PID of process blocking our lock */
    /*                                (set by F_GETLK and F_OFD_GETLK) *1/ */
    /*            ... */
    /*        }; */

	printf("im locking a file with a section number %d!!\n", section_no);
	locker.l_whence = SEEK_SET;
	locker.l_start = SECTION_SIZ * section_no;
	locker.l_len = SECTION_SIZ;

    fcntl(fd, F_OFD_SETLKW, &locker);

	char input;
	puts("file lock is over! im waiting for user input, 'q' to exit");
	while((input=getc(stdin)) != 'q'){}

	puts("im unlocking the file!! good bye");
	locker.l_type = F_UNLCK;
	fcntl(fd, F_OFD_SETLKW, &locker);
	close(fd);

    return EXIT_SUCCESS;

err:
	print_usage(argv[0]);
	return EXIT_FAILURE;
}

static inline int open_file(void)
{
    int fd;
    fd = open(LOCK_FILENAME, O_RDWR | O_CREAT, 0644);
    INSPECT(fd!=-1, return -1;);
    return fd;
}
