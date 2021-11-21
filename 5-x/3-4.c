#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;
	stat("unix.txt", &buf);
	
	printf("Mode = %o (16진수: %x)\n",(unsigned int)buf.st_mode,(unsigned int)buf.st_mode);
	if (S_ISFIFO(buf.st_mode))
		printf("unix.txt : FIFO\n");
	if (S_ISDIR(buf.st_mode))
		printf("unox.txt : Directory\n");
	if (S_ISREG(buf.st_mode))
		printf("unix.txt : Regular Fille\n");
	return 0;
}
			
