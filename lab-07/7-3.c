#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int pd[2];
	char str[] = "Pipe test";
	char buf[BUFSIZ];
	int len, status;
	// 파이프 생성하기	
	if(pipe(pd) == -1)
	{
		// 만약 오류가 있다면 에러문구를 출력후 종료한다.
		perror("pipe Error");
		exit(1);
	}
	
	// pd[1] 즉 write영역에 str정보를 입력
	write(pd[1], str, strlen(str));
	printf("%d wirtes %s to the pipe.\n",(int)getpid(), str);
	// 파이프의 read에서 정보 읽기
	len = read(pd[0], buf, BUFSIZ);
	// 해당 정보를 출력
	printf("%d reads %s from the pipe.\n", (int)getpid(), buf);
	
	// 파이프 닫기
	close(pd[0]);
	close(pd[1]);
	
	return 0;
}
