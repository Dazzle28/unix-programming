#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

int main(void) {
    char buffer[81];
    struct termios oldterm, newterm;
    int fd = open("/dev/tty", O_RDWR, 0);
    FILE *fp = fdopen(fd, "w+");

    tcgetattr(fd, &oldterm);
    newterm = oldterm;
    newterm.c_lflag &= ~ECHO;
    tcsetattr(fd, TCSAFLUSH, &newterm);

    fprintf(fp, "Enter password: ");
    fflush(fp);

    fscanf(fp, "%80s", buffer);
    putchar('\n');

    tcsetattr(fd, TCSAFLUSH, &oldterm);
    printf("Password = <%s>\n", buffer);

    return 0;
}
