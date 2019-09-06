#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SIZE 1024
int main() {
    int shmid;
    int i;
    int *shmptr;
    key_t key = ftok(getenv("HOME"), 0);

    shmid = shmget(key, SIZE * sizeof(int), 0);
    if (shmid < 0) {
        perror("shmget failed");
        exit(1);
    }

    shmptr = (int *) shmat(shmid, 0, SHM_RDONLY);
    if (shmptr == (int *) -1) {
        perror("Can't attach");
        exit(1);
    }

    for (i = 0; i < SIZE; i++)
        printf("%d:%d\n", i, shmptr[i]);
}
