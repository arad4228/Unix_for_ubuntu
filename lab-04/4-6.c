#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{	
	//만약 linux라는 디렉토리를 LINUX라고 변경하지 못했다면
	if( rename("linux", "LINUX")== -1)
	{
		//Linux라는 에러 출력 후 종료
		perror("Linux");
		exit(1);
	}
	return 0;
}
