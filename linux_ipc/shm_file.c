/*
    shared memory with file. 
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
#include<CSHutil.h>

#define SHARED_FILENAME "shared_file"
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
    fprintf(stderr, "%s <monitor | sender> [message]\n", progname);
}

// monitoring 쪽이 파일을 생성한다.
int do_monitoring(void)
{
    // file open | creat
    // mmap
    // init shared memory
    // waiting for change
    int fd;
	struct login_info *info;
	struct login_info local;

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//
//    int open(const char *pathname, int flags);
//    int open(const char *pathname, int flags, mode_t mode);
	puts("im opening");
    INSPECT( (fd = open(SHARED_FILENAME, O_RDWR | O_CREAT, 0644)) != -1,
            return -1;
           );
    // filesize == 0 인 상태에서 파일을 적지도 않고 매핑하면 정상적으로 작동하지 않는다.
    // int ftruncate(int fd, off_t length);
    // If the file previously was larger than this size, the extra data is lost.  If  the file  previously  was shorter, it is extended, and the extended part reads as null bytes ('\0').

	puts("im ftruncating!");
	INSPECT( ftruncate(fd, sizeof(struct login_info)) != -1,
			close(fd);
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

    close(fd);
	
    memset(&local, 0, sizeof(struct login_info));
    puts("im waiting for change!!");
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

	//int munmap(void *addr, size_t length);
	munmap(info, sizeof(struct login_info));
	close(fd);

	return 0;
}

int do_login(char message[MAX_BUF])
{
    // mmap
    // pid, counter 설정 struct login_info
    int fd;
	struct login_info *info;

//#include <sys/types.h>
//#include <sys/stat.h>
//#include <fcntl.h>
//
//    int open(const char *pathname, int flags);
//    int open(const char *pathname, int flags, mode_t mode);
	puts("im opening");
    INSPECT( (fd = open(SHARED_FILENAME, O_RDWR | O_EXCL, 0644)) != -1,
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

    puts("im writing!!");
    info->pid = getpid();
    info->counter++;
    strncpy(info->message, message, MAX_BUF);

	//int munmap(void *addr, size_t length);
	munmap(info, sizeof(struct login_info));
	close(fd);

	return 0;
}
