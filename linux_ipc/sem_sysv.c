#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<CSHutil.h>

#define FTOK_PATH "/tmp"
#define FTOK_PROJ_ID 'd'
#define NUM_SEM 2

static void print_usage(const char * progname)
{
    fprintf(stderr, "usage: %s <option>\n", progname);
    fprintf(stderr, "option:\n");
    fprintf(stderr, "\
      init                # initialize semaphore\n\
    | show                # show current semaphore set status\n\
    | get <SEM_IDX>       # get semaphore with index SEM_IDX\n\
    | release <SEM_IDX>   # release semaphore with index SEM_IDX\n\
    | wait0 <SEM_IDX>     # wait until semaphore value is 0 with index SEM_IDX\n\
    \n");
}

static int init_semaphore(void);
static int init(int sem_id);
static int show(int sem_id);
static int wait0(int sem_id, int sem_idx);
static int release(int sem_id, int sem_idx);
static int get(int sem_id, int sem_idx);

int main(int argc, char ** argv)
{
    int sem_idx, sem_id;
    int ret;

    INSPECT((sem_id = init_semaphore()) != -1,
            return EXIT_FAILURE;)
    
    if (argc < 2) goto err;

    if (!strcmp(argv[1], "init")){
        ret = init(sem_id);
    } 
    else if (!strcmp(argv[1], "show")) {
        ret = show(sem_id);
    } 
    else if (!strcmp(argv[1], "get")) {
        if (argc < 3) goto err;
        sem_idx = atoi(argv[2]);
        ret = get(sem_id, sem_idx);
    } 
    else if (!strcmp(argv[1], "release")) {
        if (argc < 3) goto err;
        sem_idx = atoi(argv[2]);
        ret = release(sem_id, sem_idx);
    } 
    else if (!strcmp(argv[1], "wait0")) {
        if (argc < 3) goto err;
        sem_idx = atoi(argv[2]);
        ret = wait0(sem_id, sem_idx);
    } 
    else {
        goto err;
    }


    return ret;

err:
    print_usage(argv[0]);
    return EXIT_FAILURE;
}

static int init_semaphore(void)
{
    key_t key;
    int sem_id = -1;


    INSPECT((key = ftok(FTOK_PATH, FTOK_PROJ_ID)) != -1,
            return -1;);
/* #include <sys/types.h> */
/* #include <sys/ipc.h> */
/* #include <sys/sem.h> */
/*     int semget(key_t key, int nsems, int semflg); */
    INSPECT((sem_id = semget(key, 2, IPC_CREAT | 0644)) != -1,
            return -1; );


    return sem_id;
}

static int init(int sem_id)
{
/* #include <sys/types.h> */
/* #include <sys/ipc.h> */
/* #include <sys/sem.h> */
/*     int semctl(int semid, int semnum, int cmd, ...); */
    semctl(sem_id, 0, SETVAL, 1);   // binary semaphore
    semctl(sem_id, 1, SETVAL, 3);   // counting semaphore to 3

    return 0;
}
static int show(int sem_id)
{
    int i;
    for (i = 0; i < NUM_SEM; i++)
    {
        printf("semaphore[%d] = %d\n", i, semctl(sem_id, i, GETVAL));
    }
    return 0;
}
static int wait0(int sem_id, int sem_idx)
{
    struct sembuf buf;
/* unsigned short sem_num;  /1* semaphore number *1/ */
/* short          sem_op;   /1* semaphore operation *1/ */
/* short          sem_flg;  /1* operation flags *1/ */
    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = 0;     // semaphore 값이 0이 될 때까지 기다림.

/*     int semop(int semid, struct sembuf *sops, size_t nsops); */
    semop(sem_id, &buf, 1);

    return 0;
}
static int release(int sem_id, int sem_idx)
{
    struct sembuf buf;
/* unsigned short sem_num;  /1* semaphore number *1/ */
/* short          sem_op;   /1* semaphore operation *1/ */
/* short          sem_flg;  /1* operation flags *1/ */
    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = 1;     // semaphore 해제

/*     int semop(int semid, struct sembuf *sops, size_t nsops); */
    semop(sem_id, &buf, 1);

    return 0;
}
static int get(int sem_id, int sem_idx)
{
    struct sembuf buf;
/* unsigned short sem_num;  /1* semaphore number *1/ */
/* short          sem_op;   /1* semaphore operation *1/ */
/* short          sem_flg;  /1* operation flags *1/ */
    memset(&buf, 0, sizeof(buf));
    buf.sem_num = sem_idx;
    buf.sem_op = -1;    // semaphore 획득

/*     int semop(int semid, struct sembuf *sops, size_t nsops); */
    semop(sem_id, &buf, 1);

    return 0;
}
