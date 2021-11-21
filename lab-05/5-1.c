#include <unistd.h>
#include <stdio.h>

int main(void)
{
	// argv[]와 envp[]를 합한 최대 크기로 byte단위이다.
	printf("Argv and Envp total: %ld\n", sysconf(_SC_ARG_MAX));
	// 한 UID에 허용되는 최대 프로세스 개수
	printf("One UID Max Process: %ld\n", sysconf(_SC_CHILD_MAX));
	// 초당 클록 틱수를 출력
	printf("Clock Tick: %ld\n", sysconf(_SC_CLK_TCK));
	// 프로세스 당 열 수 있는 최대 파일 개수를 출력
	printf("Max Open File: %ld\n", sysconf(_SC_OPEN_MAX));
	// 시스템이 지원하는 POSIX.1의 버전 출력
	printf("System's POSIX version: %ld\n", sysconf(_SC_VERSION));
	return 0;
}
