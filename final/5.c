#include <stdio.h>
#include <sys/ucontext.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handler(int signo)
{
	;
}

int main(void)
{
	// 
	struct sigaction act;

	// sa_mask를 초기화 한다.
	sigemptyset(&act.sa_mask);
	// SIGQUIT를 sa_mask에 설정을 추가한다.
	sigaddset(&act.sa_mask, SIGQUIT);
	//특별한 행동을 정의하지 않으므로 0으로 초기화한다.
	act.sa_flags = 0;
	// action이 발생했을 때 동작할 handler를 정의한다.
	act.sa_handler = handler;
	// 시그널 핸들러를 지정한다.
	if(sigaction(SIGINT, &act, (struct sigaction *)NULL) < 0)
	{
		// 시그널 지정에 문제가 있다면 오류를 출력하고 종료
		perror("sigaction");
		exit(1);	
	}
	short i = 0;
	while(1)
	{
		if(i< 0)
			i = 0;
		printf("%d\r", i++);
	}

	return 0 ;
}
