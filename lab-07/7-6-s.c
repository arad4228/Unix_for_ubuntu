#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int pd, n;
	char msg[] = "Hello FIFO";
	
	printf("Server =====\n");
	
	if (mkfifo("./TESTFIFO", 0666) == -1)
	{
		perror("mkfifo");
		exit(1);
	}
	
	if ((pd = open("./TESTFIFO", O_WRONLY)) == -1)
	{
		perror("open");
		exit(1);
	}
	
	printf("TO client: %s\n", msg);
	
	n = write(pd, msg, strlen(msg) +1);
	if (n == -1)
	{
		perror("wirte");
		exit(1);
	}
	close(pd);
	
	return 0;
}
