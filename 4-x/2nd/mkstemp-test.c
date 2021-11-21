#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char fname[10] = "tempXXXXXX";
	char str[] = "test str";
	int fd;

	fd = mkstemp(fname);
	write(fd,str, sizeof(str)-1);
	close(fd);
	
	return 0;
}
