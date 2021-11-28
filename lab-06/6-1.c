#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{	
	// pid를 저장할 공간
	pid_t pid;
	
	// 자식프로세스를 생성하는데 오류가 났다면 
	if((pid = fork()) < 0)
	{
		//fork를 출력하고 종료
		perror("fork");
		exit(1);
	}
	// 그렇지않고 pid 가 양수이면 즉 부모 프로세스이면
	if(pid > 0)
	{
		// 2초간 쉬디가 아래 해당 출력문을 출력
		sleep(2);
		// 자신의pid와 자신의 부모의 pid를 출력.
		printf("Parent process has pid = %d ppid = %d\n", (int)getpid()
		, (int)getppid());
	}
	// 그렇지 않고 자식 프로세스라면
	else
		// 자식도 역시 해당 출력문을 출력
		printf("Child process has pid = %d ppid = %d\n", (int)getpid()
		, (int)getppid());
	printf("End of fork ...\n");
	
	return 0;
}
