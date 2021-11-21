#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd, flags;
	
	fd = open("unix.txt", O_RDWR);
	if(fd == -1)
	{
		perror("open");
		exit(1);
	}	
	
	if((flags = fcntl(fd, F_GETFL)) == -1)
	{
		perror("fcntl");
		exit(1);
	}
	
	flags |= O_APPEND;
	
	if(fcntl(fd, F_SETFL, flags) == -1)
	{
		perror("fcntl");
		exit(1);
	}
	
	if(write(fd,"Hanbit Media", 12) != 12)
		perror("write");
	close(fd);
	return 0;
}
