#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#define MAXBUF 1024

void CHLDhandler(int sig) {
    while (waitpid(0, NULL, WNOHANG) > 0) {
    }
}

void TERMhandler(int sig) {
    printf("Server closing down\n");
    exit(0);
}

int main(int argc, char *argv[]) {
    char buffer[MAXBUF];
    struct sockaddr_in addr;
    struct hostent *host;
    size_t addrlen;
    int n;
    int sockfd, commfd, pid;

    signal(SIGCHLD, CHLDhandler);
    signal(SIGTERM, TERMhandler);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket failed");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(2000);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*) &addr, sizeof(addr)) < 0) {
        perror("socket failed");
        exit(1);
    }

    if (listen(sockfd, 5) < 0) {
        perror("listen failed");
        exit(1);
    }

    for (;;) {

        /* Loop waiting for requests and servicing them */

        addrlen = sizeof(addr);
        commfd = accept(sockfd, (struct sockaddr*) &addr,
                (socklen_t*) &addrlen);

        if (commfd < 0) {
            /* Just a minor interruption, go back and wait again... */
            if (errno == EINTR)
                continue;
            perror("accept failed");
            exit(1);
        }

        /* Print message to say who is calling... */

        host = gethostbyaddr((char*) &addr.sin_addr, sizeof(struct in_addr),
                AF_INET);
        printf("Connection from host %s (%s) on port %d\n",
                host ? host->h_name : inet_ntoa(addr.sin_addr),
                inet_ntoa(addr.sin_addr), addr.sin_port);

        /* Now deal with the request */

        switch (pid = fork()) {
        case -1:
            perror("fork failed");
            exit(1);

        case 0:
            /* Child process - handle request */
            close(sockfd);

            while ((n = read(commfd, buffer, MAXBUF)) > 0)
                printf("Message; %s\n", buffer);

            if (n < 0) {
                perror("read failed");
                exit(1);
            }
            exit(0);

        default:
            /* Parent process - go back and wait for next request */
            close(commfd);

        }
    }
    return 0;
}
