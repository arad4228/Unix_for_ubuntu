#include <unistd.h>
#include <signal.h>
#include <stdio.h>

void handler(int signo) 
{
    	psignal(signo, "Received Signal");
}

int main(void) 
{
    	signal(SIGALRM, handler);

    	alarm(2);
    	printf("Wait...\n");
    	sleep(3);

    	return 0;
}
