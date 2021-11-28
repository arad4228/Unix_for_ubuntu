#include <stdio.h>

int main(void)
{
	int i;
	// 출력문을 찍고 1초 쉰다.
	for(i = 0; i < 10; i++)
	{
		printf("sleep 1 second...\n");
		sleep(1);
	}	
	return 0;
}
