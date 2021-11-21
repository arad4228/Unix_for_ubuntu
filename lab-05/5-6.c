#include <stdio.h>

int main(void)
{
	int i;
	long s = 0;
	
	// 0부터 1000000까지 더하는 부분	
	for (i = 0; i <= 1000000; i++)
		s = s + i;
	//결과 출력
	printf("%ld\n", s);
	
	return 0;
}
