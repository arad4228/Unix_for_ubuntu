#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

int main(void)
{
	int pd[2];
	pid_t pid;
	char str[] = "Pipe test";
	char buf[BUFSIZ];
	int len, status;
	// 파이프 생성하기	
	if(pipe(pd) == -1)
	{
		// 오류가 있다면 출력하고 종료
		perror("Pipe Error");
		exit(1);
	}
	
	switch(pid = fork())
	{
		// 오류의 상황에서는 오류를 출력하고 종료
		case -1:
			perror("fork Error");
			exit(1);
			break;
		// 자식 프로세스의 동작
		case 0:
			// 자식은 파이프에서 읽을 것이므로 종료
			close(pd[1]);
			// 파이프에서 정보를 읽어온다.
			len = read(pd[0], buf, BUFSIZ);
			printf("%d read '%s' from the pipe.\n", (int)getpid(), buf);
			break;			
		default:
			// 부모는 파이프에서 데이터를 저장만 할 것이므로 종료
			close(pd[0]);
			write(pd[1], str, strlen(str));
			printf("%d write data\n", (int)getpid());
			wait(NULL);
			break;
	}	
	// 파이프 닫기
	close(pd[0]);
	close(pd[1]);
	
	return 0;
}
