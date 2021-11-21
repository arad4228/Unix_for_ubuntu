#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SIZE 4096

int main(void)
{
	// 파일 기술자 2개를 생성.
	int fdin, fdout, n;
	// 데이터를 저장할 공간 생성 크기는 미리 지정된 크기
	char  buf[SIZE];
	
	// dummy 파일을 읽기 오류가 발생하면 Open dummy를 오류를 내고 종료
	fdin =  open("dummy", O_RDONLY);
	if(fdin == -1)
	{
		perror("Open dummy");
		exit(1);
	}
	
	// copy한 파일을 쓰기 위한 open 쓰기전용, 없으면 생성, 이미있고 쓰기옵션이면 지우고  길이0으로 고정하고 권한은 0644로 한다.
	// 오류가 발생시  Write copy를 출력후 종료
	fdout = open("copy", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if(fdout == -1)
	{
		perror("Write copy");
		exit(1);
	}
	// 파일을 읽고 복사하는 과정
	while ( (n = read(fdin, buf, SIZE)) > 0)
		if(write(fdout, buf,SIZE) != n)
			perror("write");

	// 열었단 기술자를 닫는다.
	close(fdin);
	close(fdout);
	
	return 0;
}
