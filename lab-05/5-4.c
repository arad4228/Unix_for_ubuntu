#include <unistd.h>
#include <stdio.h>

int main(void)
{	
	// 현재 프로세스의 PID를 가져오기
	printf("PID : %d\n", (int)getpid());
	// 현재 프러세스의 부모 프로세스의 PID를 가져오기
	printf("PPIF : %d\n", (int)getppid());
	
	return 0;
}
