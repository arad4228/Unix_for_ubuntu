#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) 
{
    	int pd, n;
    	char msg[] = "Hello, FIFO";

    	printf("a =====\n");

    	if (mkfifo("./H_FIFO", 0666) == -1) 
	{
        	perror("mkfifo");
        	exit(1);
    	}

    	if ((pd = open("./H_FIFO", O_WRONLY)) == -1) 
	{
        	perror("open");
        	exit(1);
    	}

    	printf("To b : %s\n", msg);

    	n = write(pd, msg, strlen(msg)+1);
    	if (n == -1) 
	{
        	perror("write");
       		exit(1);
    	}
    	close(pd);

    	return 0;
}
