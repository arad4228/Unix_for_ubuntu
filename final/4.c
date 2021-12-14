#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    	int pd[2];
    	pid_t pid;
	
	// 파이프를 생성한다.
    	if (pipe(pd) == -1) 
	{
		// 만약 오류가 있다면 출력하고 종료한다.
        	perror("pipe");
        	exit(1);
    	}
	
	// fork를 통해 자식 프로세스를 생성한다.
    	switch (pid = fork()) 
	{
		// 정상적이지 않은 경우
        	case -1 :
			// 에러를 출력하고 종료한다.
            		perror("fork");
            		exit(1);
            		break;
        	case 0 : /* child의 경우이다. */
            		// pd[0]을 닫는다.
			close(pd[0]);
			// pd[1]이 닫아져있지 않다면
            		if (pd[1] != 0) 
			{
				// pd[1]을 stdout자리에 넣는다.
                		dup2(pd[1], 1);
				// pd[1]을 닫는다.
                		close(pd[1]);
            		}
			// ls명령어를 실행한다.
           		execlp("ls", "ls", "-l", (char *)NULL);
			// 오류가 발생했다면 종료
            		exit(1);
            		break;
        	default : /* parent의 경우이다. */
			//pd[1]을 닫는다.
            		close(pd[1]);
			// pd[0]이 닫아져있지 않다면
            		if (pd[0] != 1) 
			{
				// pd[0]를 stdin자리에 넣는다.
                		dup2(pd[0], 0);
				// pd[0]을 닫는다.
                		close(pd[0]);
            		}	
			// "c"에 대한 grep명령어를 실행한다.
            		execlp("grep", "grep", "c", (char *)NULL);
            		// 자식이 종료하길 기다린다.
			wait(NULL);
			break;
    	}

    	return 0;
}
