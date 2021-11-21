#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	int i, sum = 0;
	
	// argc번 만큼
	// argv의 값을 int로 변환해서 sum에 더해준다.
	for(i = 1;i < argc; i++)
		sum += atoi(argv[i]);
	
	// sum의 값을출력
	printf("%d\n",sum);
	return 0;
}
