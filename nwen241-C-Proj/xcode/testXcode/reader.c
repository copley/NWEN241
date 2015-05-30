#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_BUF 1024

int main()
{
  int fd;  // file descriptor 
  char * myfifo = "myfifo"; // declare the name of the pipe
  char buf[MAX_BUF]; // our buffer for reading up to MAX_BUF chars

  /* open, read, and display the message from the FIFO */
  fd = open(myfifo, O_RDONLY); // open read only and blocking
  read(fd, buf, MAX_BUF); // read from the pipe into buf
  printf("Received: %s\n", buf); // let us know what has been read
  close(fd); // good practice to close our pipe

  return 0;
}
