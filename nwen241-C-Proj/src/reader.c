#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
    int fdW;
    char * fifoW = "fifoW";
    char buf[MAX_BUF]; /* define max buffer size */
    
    /* open, read, and display the message from the FIFO */
    do {
        sleep(3); /* insert a wait so that the other process has time to create the pipe */
        fdW=open(fifoW, O_RDONLY);
    } while(fdW == -1); /* loop until we successfully open the pipe */
    if (fdW < 0)
    {
        printf("open fifo error: %d\n", fdW);
    }
    
    read(fdW, buf, MAX_BUF); /* read from the pipe into buf */
    printf("Received: %s\n", buf);
    close(fdW);
    
    /* reopens the pipe in write mode to send Hello back*/
    fdW=open(fifoW, O_WRONLY);
    write(fdW, "Hello", sizeof("Hello"));
    close(fdW);

    return 0;
}
