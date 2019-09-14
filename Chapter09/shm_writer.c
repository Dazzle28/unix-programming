#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 1024
int main() {
    int shmid;
    int *shmptr;
    int i;
    key_t key = ftok(getenv("HOME"), 0);

    shmid = shmget(key, SIZE * sizeof(int), IPC_CREAT | S_IRWXU);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    shmptr = (int *) shmat(shmid, 0, 0);
    if (shmptr == (int *) -1) {
        perror("Can't attach");
        exit(1);
    }

    for (i = 0; i < SIZE; i++)
        shmptr[i] = i * 2;
}
