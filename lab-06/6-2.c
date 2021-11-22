#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	// pid를 저장할 공간
	pid_t pid;
	
	// 3번 반복할 것이므로 for문을 통해 반복
	for(int i = 0; i< 3; i++)
	{
		// fork를 통해 자식 프로세스를 생성.
		switch(pid = fork())
		{
			// fork가 제대로 생성되지 않았다면 fork를 발생하고 종료
			case -1:
				perror("fork");
				exit(1);
				break;
			// 자식프로세스의 동작
			case 0:
				// 해당 출력문을 출력후 종료한다.
				printf("My pid is %d and ppid is %d\n", (int)getpid(), (int)getppid());
				return 0;
			
			default:
				// 만약 부모프로세스가 먼저 실행 되었다면 자식을 기다리고 아무것도 하지않는다.
				wait(NULL);
		}
	}

	return 0;
}
