#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(void)
{
	int i;
	// 출력문을 찍고 1초 쉰다.
	for(i = 0; i < 10; i++)
	{
		// sigset을 통해 SIGINT 즉 ctrl+C를 SIG_IGN으로 처리하도록 한다.
		// 그리고 만약 설정이 오류가 났다면 
		if(sigset(SIGINT, SIG_IGN) == SIG_ERR)
		{
			// sigset을 출력후 종료
			perror("sigset");
			exit(1);
		}
		printf("sleep 1 second...\n");
		sleep(1);
	}	
	return 0;
}
