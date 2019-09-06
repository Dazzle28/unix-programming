#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

void init_daemon(void);

int main() {
    init_daemon();
    for (;;) {
    }
    return 0;
}

void init_daemon() {
    pid_t pid;
    int i;
    pid = fork(); /* child process cannot be group leader */
    if (pid > 0)
        exit(0); /* let parent die */

    setsid(); /* become new session leader */

    chdir("/"); /* work in root directory */

    for (i = 0; i < 1024; i++) /* ensure all files closed */
        close(i);
    open("/dev/null", O_RDWR); /* open stdin to null device */
    dup2(0, 1); /* also stdout */
    dup2(0, 2); /* also stderr */
}

