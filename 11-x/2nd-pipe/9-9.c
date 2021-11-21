#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(void)
{
	char msg[] = "Hello FIFO";
	char buf[BUFSIZ];
	int pd, n;

	if(mkfifo("T_FIFO", 0644) == -1)
	{
		perror("mkfifo");
		exit(1);
	}
	
	if((pd = open("./T_FIFO", O_RDWR)) == -1)
	{
		perror("open");
		exit(2);
	}
	
	n = write(pd, msg, strlen(msg)+1);
	if (n == -1)
	{
		perror("write");
		exit(3);
	}
	
	n = read(pd, buf, BUFSIZ);
	write(1,buf, n);
	write(1, "\n", 1);

	close(pd);

	return 0;
}	
