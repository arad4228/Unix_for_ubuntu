#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo)
{
	// signal에 대한 정보를 print후 5초를 쉬고 나머지 구문을 출력한다.
	psignal(signo, "Received Signal:");
	sleep(5);
	printf("In Signal Handler, After Sleep\n");
}

int main(void)
{
	// signal 집합에 대한 구조체 생성.
	struct sigaction act;
	// 모든 시그널 집합에 대한 시그널을 처리하는 동안 블록화할시그널 집합의마스크를 비운다.
	sigemptyset(&act.sa_mask);
	// 시그널을 어떻게 제어할 것인지에 대한 설정을 0으로 설정한다.
	act.sa_flags = 0;
	// 시그널 집합의 action을 처리할 handler함수를 만든handler함수로 설정한다.
	act.sa_handler = handler;
	// signal이나 signalset이 왔을 때 이를처지하는함수를 등록한다.
	// SIGINT에 대해 설정할 action을 넣고 기존의값은 저장하지 않는다.
	if(sigaction(SIGINT, &act, (struct sigaction *)NULL)  < 0)
	{
		// 오류 발생시 sigaction을 출력하고 종료
		perror("sigaction");
		exit(1);
	}
	// 무한 반복한다.
	while(1)
	{
		// standard err을 통해 출력한다.
		fprintf(stderr, "Input SIGINT: ");
		pause();
		fprintf(stderr, "After Signal Handler\n");
	}
	return 0;
}
