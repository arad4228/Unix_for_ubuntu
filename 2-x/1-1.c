#include <unistd.h>
#include <stdio.h>

extern int errno;

int main(void)
{
	if(access("unix.txt",F_OK) == -1)
		printf("errono=%d\n",errno);
	
	return 0;
}	
