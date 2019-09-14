#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define MAXBUF 1024
#define CLEAR(S) memset((void*)&S, '\0', sizeof(S))

int main(int argc, char *argv[]) {
    char msg[MAXBUF];
    struct sockaddr_in addr;
    int n;
    int sockfd;

    sprintf(msg, "Test message from client [%d]", getpid());

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2000);
    addr.sin_addr.s_addr = inet_addr(argv[1]);

    n = connect(sockfd, (struct sockaddr*) &addr, sizeof(addr));
    if (n < 0) {
        perror("connect failed");
        exit(1);
    }

    n = write(sockfd, msg, strlen(msg) + 1);
    if (n < 0) {
        perror("write failed");
        exit(1);
    }

    return 0;
}
