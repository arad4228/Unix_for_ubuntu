#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	int i, status;
	
	// fork를 통해 자식 프로세스를 생성.
	if((pid = fork()) < 0)
	{
		// 오류가 났다면 fork를 띄우고 종료
		perror("fork");
		exit(1);
	}
	// 부모 프로세스의 동작
	if(pid > 0)
	{
		// 해당 출력문을 출력후
		printf("Parent %d waits child %d\n", (int)getpid(), (int)pid);
		// 자식 프로스세스가 끝날 때까지 대기
		wait(&status);
		// 해당 문을 출력
		printf("Child's exit status = %x\n", status);	
		printf("Child's exit status = %d\n", status >> 8);
	}
	// 자식프로세스의 동작
	else
	{
		// 자식 프로세스는 출력문을 찍고 1초 쉬고를 5번 반복한다. 
		for(i = 0; i < 5; i++)
		{
			printf("Child %d executes.\n", (int)getpid());
			sleep(1);
		}
		// 3을 넘기면서 종료한다.
		exit(3);
	}
	
	return 0;
}
