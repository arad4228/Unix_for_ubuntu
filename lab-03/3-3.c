#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	//파일을 읽고 쓰려는 2개의 기술자를 선언
	int rfd, wfd, n;
	char buf[BUFSIZ];
	
	//읽기 전용으로 파일 읽기
	rfd = open("3-1.txt", O_RDONLY);
	//파일이 읽히지않았다면 오류 출력
	if (rfd == -1)
	{
		perror("Open");
		exit(1);
	}
	
	//파일을 쓰기 파일이 없으면 생성과 쓰기로 열고 이미 생성했다면 내용을 비우기를 추가
	// 파일을 읽고 복사하므로 이미있다면 대체하는 경우 생각.
	wfd = open("3-3.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	//쓰기를 위한 열기 문제시 오류 발생
	if(wfd == -1)
	{
		perror("Open fail 3-3.txt");
		exit(1);
	}
	// 버퍼에 BUFSIZ만큼 읽고 해당 내용을 3-3.txt에 쓰기
	while((n = read(rfd, buf, BUFSIZ)) > 0)
		if ( write(wfd,buf,n) != n)
			perror("Writr error");

	return 0;
}	
