#include "../headers.h"

int main(void) {
    pid_t pid;

    if ((pid = getpid()) == -1) {
        perror("Failed to get pid");
        exit(1);
    }

    printf("Your process id is %d\n", pid);

    return 0;
}
