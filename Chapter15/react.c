#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

int main(void) {
    struct termios oldterm, newterm;
    struct tms tbuf;
    clock_t start, end;
    int n;
    char ch = '\a';

    if (tcgetattr(0, &oldterm) < 0) {
        perror("tcgetattr failed");
        exit(1);
    }

    newterm = oldterm;
    newterm.c_lflag &= ~(ICANON | ECHO);
    newterm.c_cc[VMIN] = 0;
    newterm.c_cc[VTIME] = 50;
    if (tcsetattr(0, TCSAFLUSH, &newterm) < 0) {
        perror("tcgetattr failed");
        exit(1);
    }

    printf("Press any character when you hear the bell? ");
    fflush(stdout);
    srand(times(&tbuf));
    sleep(rand() % 7 + 3);
    write(1, &ch, 1);

    start = times(&tbuf);
    n = read(0, &ch, 1);
    end = times(&tbuf);

    tcsetattr(0, TCSAFLUSH, &oldterm);
    putchar('\n');

    if (n == 0)
        printf("Too s l  o   w     !\n");
    else
        // printf("Time: %.3f seconds\n", (double) (end - start) / CLK_TCK);
        printf("Time: %.3f seconds\n", (double) (end - start) / 1000.0);
    return !n;
}
