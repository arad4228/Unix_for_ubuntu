#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    	char *argv[3];
    	char *envp[2];

    	printf("Before exec function\n");

    	argv[0] = "6-6-arg";
    	argv[1] = "100";
    	argv[2] = NULL;

    	envp[0] = "MYENV=LINUX";
    	envp[1] = NULL;

    	if (execve("./6-6-arg", argv, envp) == -1) 
	{
        	perror("execve");
        	exit(1);
    	}

    	printf("After exec function\n");

    	return 0;
}
