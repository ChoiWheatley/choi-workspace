#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<assert.h>
#include<errno.h>

#define SOCK_PATH "sock_stream_un"
#define MAXBUF      4096

#define INSPECT(expr, then) \
    if ((expr)==0) {\
        fprintf(stderr, "in function(%s), line number(%d),\n", __func__, __LINE__);\
        fprintf(stderr, "`%s` has error occured!\n", #expr);\
        then\
    }

size_t wrap_send(int sock, void *buf, size_t buflen, int flag);
size_t wrap_recv(int sock, void *buf, size_t buflen, int flag);

static void print_usage(const char *progname)
{
    printf("%s <server | client>\n", progname);
}

static int do_server(void)
{
    // socket()
    // bind()
    // listen()
    // accept()
    // send / recv
    // close()

    int sock, peer, ret;
    struct sockaddr_un addr;
    char buf[MAXBUF];

//int socket(int domain, int type, int protocol);
    puts("im creating a socket descriptor");
    INSPECT( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) != -1, return -1;);

// man bind
//        int bind(int sockfd, const struct sockaddr *addr,
//        socklen_t addrlen);
// man 7 unix
//        #include <sys/socket.h>
//        #include <sys/un.h>
//        Address format
//        A UNIX domain socket address  is  represented  in  the  following
//        structure:
//
//        struct sockaddr_un {
//            sa_family_t sun_family;               /* AF_UNIX */
//            char        sun_path[108];            /* Pathname */
//        };
    // unlink to delete socket file
//           int unlink(const char *pathname);
    unlink(SOCK_PATH);
    puts("im binding");
    memset(&addr, 0, sizeof(addr));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);
    INSPECT(
            bind(sock,(const struct sockaddr*)&addr, sizeof(struct sockaddr)) != -1,
            return -1;
           );

// listen
//        int listen(int sockfd, int backlog);
    puts("im listening");
    INSPECT(
            listen(sock, 5) != -1,
            return -1;
           );
// accept
//       int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    puts("im accepting");
    INSPECT(
            (peer = accept(sock, NULL, NULL)) != -1,
            close(sock);
            return -1;
    );

// recv
//        ssize_t recv(int sockfd, void *buf, size_t len, int flags);
    puts("im receiving");
    memset(buf, 0, sizeof(buf));
    INSPECT(
            (ret = wrap_recv( peer, buf, sizeof(buf), 0 )) != -1,
            close(sock);
            return -1;
    );
    printf("client said `%s`\n", buf);

    puts("im closing");
    close(peer);
    close(sock);

    return ret;
}

size_t wrap_recv(int sock, void *buf, size_t buflen, int flag)
{
    int received = 0, amt;
    while(received < buflen)
    {
        // 앞의 바이트를 건너뛰고 나머지를 전송한다.
        amt = recv(sock, (char *)buf + received, 
                   buflen - received, flag);
        if (amt < 0)
            return amt;
        received+=amt;
    } 
    return received;
}
static int do_client(void)
{
//socket
//connect
//send/recv
//close
    int sock, ret;
    struct sockaddr_un addr;
    char buf[MAXBUF];

    // socket
    puts("im creating a socket");
    INSPECT( (sock = socket(AF_UNIX, SOCK_STREAM, 0)) != -1, return -1;);

    // connect
// int connect(int sockfd, const struct sockaddr *addr,
//             socklen_t addrlen);
    puts("im connecting");
    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    snprintf(addr.sun_path, sizeof(addr.sun_path), SOCK_PATH);
    INSPECT(
            connect(sock, (struct sockaddr*)&addr, 
                sizeof(struct sockaddr_un)) != -1,
            close(sock);
            return -1;
           );

    // send
    puts("im sending");
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "this is message from sock_stream! hello world!");
    INSPECT(
            (ret = wrap_send(sock, buf, sizeof(buf), 0)) != -1,
            close(sock);
            return -1;
           );
    
    puts("im closing");
    close(sock);

    return ret;
}

size_t wrap_send(int sock, void *buf, size_t buflen, int flag)
{
    int written = 0, amt=0;
    while( written < buflen )
    {
        // 앞의 바이트를 건너뛰고 나머지를 전송한다.
        amt = send(sock, (char *)buf + written, 
                buflen - written, 
                flag);
        if (amt < 0)
            return amt;
        written+=amt;
    }

    return written;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
    int ret=0;

    if (!strcmp(argv[1], "server")) {
        if( (ret=do_server()) == -1 )
            perror(strerror(errno));
    } else if (!strcmp(argv[1], "client")) {
        if( (ret=do_client()) == -1)
            perror(strerror(errno));
    } else {
        print_usage(argv[0]);
        ret = EXIT_FAILURE;
    }
    return ret;
}
