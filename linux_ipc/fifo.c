/*
 * named pipe can read or write from unrelated processes
 * fifo (reader | writer)
 * named pipe는 읽는 API, 쓰는 API가 서로 구분되어있다.
 * 
*/

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define FIFO_FILENAME       "./testfifo"
#define MAXBUF              4096

static void print_usage(char *progname)
{
    printf("usage: %s <r|w>\n", progname);
}

static int do_reader(void)
{
    int fd;
    char buf[MAXBUF];

    fd = open(FIFO_FILENAME, O_RDONLY | O_CREAT);
    if (fd<0)
    {
        perror("open()");
        return -1;
    }

    read(fd, buf, sizeof(buf));
    printf("writer said\"%s\"\n", buf);
    close(fd);

    return 0;
}
static int do_writer(void)
{
    int fd;
    char buf[MAXBUF];

    unlink(FIFO_FILENAME);
    if (mkfifo(FIFO_FILENAME, 0644))
    {
        perror("mkfifo()");
        return -1;
    }

    fd = open(FIFO_FILENAME, O_WRONLY);
    if (fd<0)
    {
        perror("open()");
        return -1;
    }
    
    scanf("%[^\n]", buf);
    //strncpy(buf, "hello", sizeof(buf));
    write(fd, buf, strlen(buf));
    close(fd);
    unlink(FIFO_FILENAME);
    
    return 0;
}

int main(int argc, char ** argv)
{
    if (argc < 2)
    {
        print_usage(argv[0]);
        return -1;
    }
    if (!strncmp(argv[1], "r", 1))
    {
        /* reader */
        do_reader();
    } 
    else if (!strncmp(argv[1], "w", 1))
    {
        /* writer */
        do_writer();
    } 
    else
    {
        print_usage(argv[0]);
        return -1;
    }

    return 0;
}
