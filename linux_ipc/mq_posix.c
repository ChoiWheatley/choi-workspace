#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include <sys/types.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
/*
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
//
//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
//        int msgflg);
*/


#define IPC_KEY_FILENAME                "/hello"  
#define MAXBUF_SIZ                      8192

static void print_usage(const char *progname)
{
    printf("%s <send PRIORITY | recv> \n", progname);
}
static int init_msgq(void)
{
#if 0
//       #include <fcntl.h>           /* For O_* constants */
//       #include <sys/stat.h>        /* For mode constants */
//       #include <mqueue.h>
//
//       mqd_t mq_open(const char *name, int oflag);
//       mqd_t mq_open(const char *name, int oflag, mode_t mode,
//                     struct mq_attr *attr);

//       Link with -lrt.

           struct mq_attr {
               long mq_flags;       /* Flags (ignored for mq_open()) */
               long mq_maxmsg;      /* Max. # of messages on queue */
               long mq_msgsize;     /* Max. message size (bytes) */
               long mq_curmsgs;     /* # of messages currently in queue
                                       (ignored for mq_open()) */
           };
#endif //0
	mqd_t mqd;
	struct mq_attr attr;

	mqd=mq_open(IPC_KEY_FILENAME, O_CREAT | O_RDWR, 0644, NULL);
	if (mqd == -1)
	{
		perror("mq_open()");
		return -1;
	}


	// 현재 디폴트로 되어있는 메시지 큐 설정을 변경한다.
//int mq_setattr(mqd_t mqdes, const struct mq_attr *newattr,
//	struct mq_attr *oldattr);
//           struct mq_attr {
//               long mq_flags;       /* Flags: 0 or O_NONBLOCK */
//               long mq_maxmsg;      /* Max. # of messages on queue */
//               long mq_msgsize;     /* Max. message size (bytes) */
//               long mq_curmsgs;     /* # of messages currently in queue */
//           };
//

	if (mq_getattr(mqd, &attr) == -1)
	{
		perror(__func__);
		close(mqd);
		return -1;
	}
	printf("[flags,maxmsg,msgsize,curmsgs]=[%ld,%ld,%ld,%ld]\n",
		attr.mq_flags 	,
		attr.mq_maxmsg  ,
		attr.mq_msgsize ,
		attr.mq_curmsgs
	);
    return mqd;
}

static int do_send(unsigned int prio)
{
    int mqd;
	char buf[MAXBUF_SIZ];

	mqd=init_msgq();
	if (mqd==-1)
	{
		perror(__func__);
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	snprintf(buf, sizeof(buf), "hellllllo world!![%d]", getpid());
	if (mq_send(mqd, buf, sizeof(buf), prio) == -1){
		perror(__func__);
		close(mqd);
		return -1;
	}

    return 0;
}

static int do_recv(unsigned int msg_prior)
{
	int mqd;
	char buf[MAXBUF_SIZ];

	mqd=init_msgq();
	if (mqd==-1)
	{
		perror(__func__);
		return -1;
	}

	memset(buf, 0, sizeof(buf));
	if (mq_receive(mqd, buf, sizeof(buf), &msg_prior) == -1)
    {
		perror(__func__);
		close(mqd);
		return -1;
	}
    printf("received message:[%s]\n", buf);
    printf("prio:%u\n", msg_prior);

    return mqd;
}

int main(int argc, char ** argv)
{
    int ret, prio=0;
    if (argc < 2) 
    {
        goto throw;
    }

    if (!strcmp(argv[1], "send"))
    {
        if (argc == 3)
        {
            prio = atoi(argv[2]);
            if (prio<0) 
                prio *= -1;
        }
		ret = do_send((unsigned int)prio);
    } 
    else if (!strcmp(argv[1], "recv"))
    {
        if (argc == 3)
        {
            prio = atoi(argv[2]);
        }
		ret = do_recv(prio);
    }
    else
    {
        goto throw;
    }

    return ret;

throw:
    print_usage(argv[0]);
    return -1;
}
