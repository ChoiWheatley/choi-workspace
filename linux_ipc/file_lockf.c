#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>

#include"../util/CSHutil.h"

static int open_file(void);

#define FILESIZ             1024
#define NUM_SECTION         4
#define SECTION_SIZ         (FILESIZ) / (NUM_SECTION)
#define LOCK_FILENAME       ".lockf_lockfile"


static void print_usage(const char *progname)
{
	printf("usage: %s section_number\n", progname);
}

int main(int argc, char ** argv)
{
    // open file
    // fcntl() :: advisory record locking
        // cmd : record lock
        // struct flock
        // 파일의 영역을 나누어 lock section으로 사용한다.
    int fd, section_no;

	if (argc < 2) {
		goto err;
	}

	// CAVEAT: 
	// atoi() 함수는 에러처리를 안한다. undefined behavior
	section_no = strtol(argv[1], NULL, 10);


    puts("im opening a file!");
    fd = open_file();
    INSPECT(fd!=-1, return -1;);


    puts("im truncating a file!");
    INSPECT(ftruncate(fd, FILESIZ) != -1, return -1;);


	printf("im locking a file with a section number %d!!\n", section_no);
    /* off_t lseek(int fd, off_t offset, int whence); */
    lseek(fd, SECTION_SIZ * section_no, SEEK_SET);
    /* int lockf(int fd, int cmd, off_t len); */
    lockf(fd, F_LOCK, SECTION_SIZ);


	char input;
	puts("file lock is over! im waiting for user input, 'q' to exit");
	while((input=getc(stdin)) != 'q'){}

	puts("im unlocking the file!! good bye");
    lockf(fd, F_ULOCK, SECTION_SIZ);
	close(fd);

    return EXIT_SUCCESS;

err:
	print_usage(argv[0]);
	return EXIT_FAILURE;
}

static int open_file(void)
{
    int fd;
    fd = open(LOCK_FILENAME, O_RDWR | O_CREAT, 0644);
    INSPECT(fd!=-1, return -1;);
    return fd;
}
