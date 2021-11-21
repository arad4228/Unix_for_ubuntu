#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd, n;
	off_t start, cur;
	char buf[10];
	
	fd = open("unix.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("Open unix.txt");
		exit(1);
	}
	
	start = lseek(fd, 0, SEEK_CUR);
	n = read(fd,buf, 255);
	buf[n] = '\0';
	printf("Offset start =%d, Read str =%s n=%d\n",(int)start, buf, n);
	cur = lseek(fd,0,SEEK_CUR);
	printf("Offset cur=%d\n", (int)cur);
	printf("buf[n-1] = %d\n",buf[n-1]);
	
	start = lseek(fd,10, SEEK_SET);
	n = read(fd, buf, 255);
	buf[n] = '\0';
	printf("Offser start =%d, Read str =%s", (int)start, buf);
	close(fd);
	return 0;
}
