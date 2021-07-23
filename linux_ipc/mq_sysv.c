#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
/*
//int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
//
//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
//        int msgflg);
*/


#define IPC_KEY_FILENAME                "/dev/null"// 커널이 다루는 프로세스 정보 보관소
#define IPC_KEY_PROJ_ID                 'a'
#define IPC_MSG_TYPE                    'a'
#define MAXBUF_SIZ                      2048

struct msgbuf           // msgsnd, rcv를 위한 msgp
{
    long mtype;
    char buf[MAXBUF_SIZ+1];
};

static void print_usage(const char *progname)
{
    printf("%s <send | recv> <message_type>\n", progname);
}
static int init_msgq(void)
{
    int msgq;
    key_t key;
    if ((key = ftok(IPC_KEY_FILENAME, IPC_KEY_PROJ_ID)) == -1 )
    {
        perror("ftok\n");
        return -1;
    }
    if((msgq = msgget(key, 0644 | IPC_CREAT)) == -1 ) 
    {
        perror("msgget\n");
        return -1;
    }
    return msgq;
}

static int do_send(long mtype)
{
    int msgq;
    struct msgbuf mbuf;
    if (mtype <= 0)
    {
        perror("mtype is smaller or equal than 0\n");
        return -1;
    }

    assert( (msgq = init_msgq()) != -1 );

//strncpy(mbuf.buf, "hello world!", sizeof(mbuf.buf));
//      int snprintf(char *str, size_t size, const char *format, ...);
    snprintf(mbuf.buf, sizeof(mbuf.buf), "hello world!<%ld>", mtype);
    mbuf.mtype=mtype;           // message type 설정
//      int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
    if (msgsnd(msgq, &mbuf, sizeof(mbuf.buf), IPC_KEY_PROJ_ID) == -1) 
    {
        perror("msgsnd\n");
        return -1;
    }

    return 0;
}

static int do_recv(long mtype)
{
    int msgq;
    struct msgbuf mbuf;
    int ret;

    assert( (msgq = init_msgq()) != -1 );

    memset( &mbuf, 0, sizeof(mbuf) );
//ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,
//               int msgflg);
    if ( (ret = msgrcv(msgq, &mbuf, sizeof(mbuf.buf), mtype, 0)) == -1)
    {
        perror("msgrcv\n");
        return -1;
    }
    printf("received msg: mtype:%ld, msg:[%s]\n", mbuf.mtype, mbuf.buf);

    return 0;
}

int main(int argc, char ** argv)
{
    int ret;
    long mtype;
    if (argc < 3) 
    {
        goto throw;
    }

//long int strtol(const char *nptr, char **endptr, int base);
    mtype = strtol(argv[2], NULL, 10);
    if (!strcmp(argv[1], "send"))
    {
        ret = do_send(mtype);
    } 
    else if (!strcmp(argv[1], "recv"))
    {
        ret = do_recv(mtype);
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
