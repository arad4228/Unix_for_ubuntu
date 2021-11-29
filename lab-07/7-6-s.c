#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int pd, n;
	// 보낼 메시지
	char msg[] = "Hello FIFO";
	
	printf("Server =====\n");

	// FIFO 파일을 0666권한으로 생성
	if (mkfifo("./TESTFIFO", 0666) == -1)
	{
		// 오류가 발생했다면 오류를 출력후 종료
		perror("mkfifo");
		exit(1);
	}
	
	// FIFO 파일을 열기 파이프를 위해
	if ((pd = open("./TESTFIFO", O_WRONLY)) == -1)
	{
		// 문제가 발생했다면 오류를 발생후 종료
		perror("open");
		exit(1);
	}
	
	printf("TO client: %s\n", msg);
	// 클라이언트에게 보낼 메시지를 pd에 작성
	n = write(pd, msg, strlen(msg) +1);
	if (n == -1)
	{
		// 작성에 문제가 발생했다면 오류를 출력후 종료
		perror("wirte");
		exit(1);
	}
	// 파이프 닫기.
	close(pd);
	
	return 0;
}
