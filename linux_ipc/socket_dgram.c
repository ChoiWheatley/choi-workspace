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

#define SOCK_PATH "sock_dgram_un"
#define MAXBUF      4096

#define INSPECT(expr, then) \
    if ((expr)==0) {\
        fprintf(stderr, "in function(%s), line number(%d),\n", __func__, __LINE__);\
        fprintf(stderr, "`%s` has error occured!\n", #expr);\
        then\
    }

static void print_usage(const char *progname)
{
    printf("%s <server | client>\n", progname);
}

static int do_server(void)
{
    // socket()
    // bind()
    // sendto() / recvfrom()
    // close()

    int sock, ret;
    struct sockaddr_un addr;
    char buf[MAXBUF];

//int socket(int domain, int type, int protocol);
    puts("im creating a socket descriptor");
    INSPECT( (sock = socket(AF_UNIX, SOCK_DGRAM, 0)) != -1, return -1;);

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
            bind(sock,(struct sockaddr*)&addr, 
                sizeof(struct sockaddr_un)) != -1,
            close(sock);
            return -1;
           );

// DGRAM 타입에서는 listen과 accept가 없다.
//        int listen(int sockfd, int backlog);
//       int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// recv
//        ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,
//                        struct sockaddr *src_addr, socklen_t *addrlen);
// DGRAM 에서는 sockfd가 peer의 주소가 아닌, 소켓주소를 의미한다.
// AF_UNIX 를 사용하기 때문에 따로 src_addr를 통해 peer의 주소를 알아낼 필요는 없게된다.
    puts("im receiving");
    memset(buf, 0, sizeof(buf));
    INSPECT(
            ( ret = recvfrom( sock, buf, sizeof(buf), 0, 
                              NULL, NULL) ) != -1,
            close(sock);
            return -1;
    );
    printf("client said `%s`\n", buf);

    puts("im closing");
    close(sock);

    return ret;
}

static int do_client(void)
{
//socket
//sendto()/recvfrom()
//close
    int sock, ret;
    struct sockaddr_un addr;
    char buf[MAXBUF];

    // socket
    puts("im creating a socket");
    INSPECT( (sock = socket(AF_UNIX, SOCK_DGRAM, 0)) != -1, return -1;);
//
// DGRAM 방식은 connect 과정이 없다.
//// int connect(int sockfd, const struct sockaddr *addr,
////socklen_t addrlen);

    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SOCK_PATH, sizeof(addr.sun_path)-1);
    // send
//ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,
// const struct sockaddr *dest_addr, socklen_t addrlen);
    puts("im sending");
    memset(buf, 0, sizeof(buf));
    snprintf(buf, sizeof(buf), "this is message from sock_dgram! hello world!");
    INSPECT(
            ( ret = sendto(sock, buf, sizeof(buf), 0,
                           (struct sockaddr*)&addr,
                           sizeof(struct sockaddr_un)) ) != -1,
            close(sock);
            return -1;
           );
    
    puts("im closing");
    close(sock);

    return ret;
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
