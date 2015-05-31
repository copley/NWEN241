#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_BUF 1024

int main()
{
    int fdW;
    char * fifoW = "fifoW";
    char buf[MAX_BUF];

    /* create a named pipe, then write, then close */
    mkfifo(fifoW, 0666);
    fdW = open(fifoW, O_WRONLY);
    write(fdW, "Hi", sizeof("Hi"));
    close(fdW);
    
    /* reopen the pipe in read mode and waits for data in */
    fdW=open(fifoW, O_RDONLY);
    read(fdW, buf, MAX_BUF);
    printf("Received: %s\n", buf);
    close(fdW);

    /* remove the FIFO */
    unlink(fifoW);
    
    return 0;
}
