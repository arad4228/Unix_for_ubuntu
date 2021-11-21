#include <unistd.h>
#include <stdio.h>

int main(void) 
{
	sleep(3);
    	printf("PID : %d\n", (int)getpid());
    	printf("PPID : %d\n", (int)getppid());

    	return 0;
}
