#define MAXBUF 256
#define FILENAME 60
#define DATA  50
#define ERROR 10

struct message {
    long type;
    char data[MAXBUF+1];
};
