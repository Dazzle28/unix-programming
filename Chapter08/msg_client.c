#include "../headers.h"
#include <sys/ipc.h>
#include <sys/msg.h>
#include "message.h"

int main(int argc, char *argv[]) {
    int qid;
    int length = strlen(argv[1]);
    struct message mesg;
    key_t key = ftok(getenv("HOME"), 0);
    if ((qid = msgget(key, 0)) < 0) {
        perror("msgget failed");
        exit(1);
    }

    if (length == 0)
        printf("Client closing down server\n");
    else
        printf("Client requesting file %s\n", argv[1]);
    strcpy(mesg.data, argv[1]);
    mesg.type = FILENAME;
    if (msgsnd(qid, (struct msgbuf*) &mesg, strlen(mesg.data), 0) < 0) {
        perror("client msgsnd failed");
        exit(1);
    }

    if (length == 0)
        return 0;

    while ((length = msgrcv(qid, (struct msgbuf*) &mesg, MAXBUF, -DATA, 0)) > 0) {
        write(1, mesg.data, length);
    }
    if (length < 0) {
        perror("client msgrcv failed");
        exit(1);
    }

    return 0;
}
