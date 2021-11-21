#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    	char *val;

    	val = getenv("PWD");
    	if (val == NULL)
        	printf("PWD not defined\n");
    	else
        	printf("PWD = %s\n", val);

    	return 0;
}
