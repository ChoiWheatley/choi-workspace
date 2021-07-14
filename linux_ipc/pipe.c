#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(int argc, char ** argv)
{
    int pipe_fd[2];
    pid_t cpid;
    char buf[2048];
    int wstatus;

    printf("[%d] start of function\n", getpid());
    memset(buf, 0, sizeof(buf));

    if (pipe(pipe_fd)){
        perror("pipe()");
        return -1;
    }
    cpid = fork();
    if (cpid == 0)
    {
        // child process :: gonna read
        close(pipe_fd[1]);
        read(pipe_fd[0], buf, sizeof(buf));
        printf("[%d]parent saied %s\n", getpid(), buf);

        close(pipe_fd[0]);
    } 
    else if (cpid > 0)
    {
        // parent process :: gonna write
        close(pipe_fd[0]);
        strncpy(buf, "hello child!", sizeof(buf) - 1);
        write(pipe_fd[1], buf, strlen(buf));

        close(pipe_fd[1]);

        cpid = wait(&wstatus);
    }
    else
    {
        // error
        perror("fork()");
        goto err;
    }
    return 0;

err:
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    return -1;
}
