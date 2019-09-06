#include "../headers.h"

#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[])
{
    int c;
    int all=FALSE, longl=FALSE;
    char *dir=NULL;

    opterr = 0;
    while ( (c=getopt(argc, argv, "ad:l")) != EOF ) {
        printf("%i\n", optind);
        switch (c) {
            case 'a': all=TRUE;        break;
            case 'd': dir=optarg;      break;
            case 'l': longl=TRUE;      break;
            case '?': fprintf(stderr, "Unknown option %c\n", optopt);
                      exit(1);
        }
    }
    printf ("all=%s, longl=%s, dir=%s\n", all?"TRUE":"FALSE", longl?"TRUE":"FALSE", dir?dir:"<NULL>");
    for (int i=optind; i<argc; i++) {
        printf ("Argument: %s\n", argv[i]);
    }
    return 0;
}

