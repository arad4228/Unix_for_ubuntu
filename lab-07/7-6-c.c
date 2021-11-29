#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int pd, n;
	// 받은 메시지를 저장할 공간
	char inmsg[80];
	
	// 파이프를 오픈
	if((pd = open("./TESTFIFO", O_RDONLY)) == -1)
	{
		// 열기 실패했다면 오류를 출력후 종료
		perror("open");
		exit(1);
	}
	
	printf("Client =====\n");
	write(1, "From Server :", 13);
	// 80byte만큼 메시지를 읽어 stdout에 작성한다.
	while ((n = read(pd, inmsg, 80)) > 0)
		write(1, inmsg, n);

	// 읽은 문자열이 오류가 있다면
	if  ( n == -1)		
	{
		// 에러를 출력후 종료
		perror("read");		
		exit(1);
	}
	write(1,"\n",1);
	close(pd);
	
	return 0;
}
