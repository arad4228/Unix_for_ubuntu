#include <stdio.h>

int main(void)
{
	int i;
	double j;

	for(i = 0; i <20; i++)
	{
		j = i/2+i;
		printf("j is %f\n",j);
	}

	return 0;
}

