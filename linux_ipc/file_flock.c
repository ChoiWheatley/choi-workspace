#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/file.h>

#include"../util/CSHutil.h"

static void print_usage(const char *progname);
static void operation2str(int op, char* ret);
int main(int argc, char** argv)
{
    // shared lock
    // exclusive lock
    // unlock
    int ops;
    int fd;
    char input;

    if (argc < 2){
        goto err;
    }


    if (!strcmp(argv[1], "sh")){
        ops=LOCK_SH;
    } else if (!strcmp(argv[1], "ex")){
        ops=LOCK_EX;
    } else {
        goto err;
    }

    puts("im opening a file!");
#define FLOCK_FILENAME ".flock_test"
    fd = open(FLOCK_FILENAME, O_RDWR | O_CREAT, 0644);
    INSPECT(fd!=-1, return -1;);
    
    char argops[10] = {0};
    operation2str(ops, argops);
    printf("im locking a file with argument %s!\n", argops);
    flock(fd, ops);


    puts("lock finished, now im waiting for input 'q'!");
    while ((input = getc(stdin)) != 'q'){}


    puts("im unlocking!");
    flock(fd, LOCK_UN);


    return 0;

err:
    print_usage(argv[0]);
    return -1;
}
static void print_usage(const char *progname)
{
    printf("usage: %s (sh|ex)\n", progname);
}

static void operation2str(int op, char* ret)
{
    switch(op){
    case LOCK_SH:
        strcpy(ret, "LOCK_SH");
        return;
    case LOCK_EX:
        strcpy(ret, "LOCK_EX");
        return;
    /* case LOCK_UN: */
    /*     strcpy(ret, "LOCK_UN"); */
    /*     return; */
    default:
        strcpy(ret, "UNDEFINED");
        return;
    }
}
