#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    struct msqid_ds buf;
    char *home = getenv("HOME");
    key_t key = ftok(home, 0);

    int id = msgget(key, IPC_CREAT | 0666);
    if (id < 0) {
        perror("IPC message get");
        exit(1);
    }

    // check message queue is set up
    if (msgctl(id, IPC_STAT, &buf) < 0) {
        perror("IPC message STAT control");
        exit(1);
    }

    // change permissions on message queue
    buf.msg_perm.mode &= ~(S_IWGRP | S_IRWXO);
    if (msgctl(id, IPC_SET, &buf) < 0) {
        perror("IPC message STAT control");
        exit(1);
    }

    printf("Now run the command: ipcs\n");
    printf("Remove old queues with: ipcrm -q <msqid>\n");

    return 0;
}
