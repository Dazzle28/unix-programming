#include "../headers.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

int main(void) {
    int qid;
    int length;
    int fd;
    struct message mesg;
    key_t key = ftok(getenv("HOME"), 0);
    if ((qid = msgget(key, IPC_CREAT | S_IRWXU)) < 0) {
        perror("msgget failed");
        exit(1);
    }

    while ((length = msgrcv(qid, (struct msgbuf*) &mesg, MAXBUF, FILENAME, 0))
            > 0) {
        mesg.data[length] = '\0';
        printf("Server opening file %s\n", mesg.data);

        fd = open(mesg.data, O_RDONLY);
        if (fd >= 0) {
            mesg.type = DATA;
            length = 1;
            while (length > 0) {
                length = read(fd, mesg.data, MAXBUF);
                if (msgsnd(qid, (struct msgbuf*) &mesg, length, 0) < 0) {
                    perror("server msgsnd failed");
                    exit(1);
                }
            }
            close(fd);
        } else {
            strcpy(mesg.data, "could not open file\n");
            mesg.type = ERROR;
            if (msgsnd(qid, (struct msgbuf*) &mesg, strlen(mesg.data), 0) < 0
                    || msgsnd(qid, (struct msgbuf*) &mesg, 0, 0) < 0) {
                perror("server msgsnd failed");
                exit(1);
            }
        }
    }

    if (length < 0)
        perror("server msgrcv failed");

    if (msgctl(qid, IPC_RMID, 0) < 0) {
        perror("msgctl remove failed");
        exit(1);
    }
    return 0;
}
