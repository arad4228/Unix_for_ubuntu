#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{	
	// pid를 저장할 공간
	pid_t pid;
	
	// 3번 반복
	for(int i = 0; i < 3; i++)
	{
		
		// 자식 프로세스를 생성.
		switch(pid = fork())
		{
			// 오류가 발생했다면 fork를 출력후 종료
			case -1:
				perror("fork");
				exit(1);
				break;
			// 자식프로세스라면 해당 문을 출력한다.
			case  0:
				printf("My pid is %d and ppid is %d\n", 
				(int)getpid(), (int)getppid());
				return 0;
			// 부모 프로세스 정확히 하면 pid > 0인 경우 이므로
			// 아무것도 하지 않기로 했으므로 넘어간다.
			default:
				wait(NULL);		
		}
	}
	printf("End of fork\n");

	return 0;
}
