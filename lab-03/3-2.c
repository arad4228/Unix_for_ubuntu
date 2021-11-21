#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	int fd;
	int n;
	//파일에 널을 문자열
	char str[] = "UNIX SYSTEM PROGRAMMING";
	//파일을 쓰기 전용을 연다.
	fd = open("3-1.txt", O_WRONLY);
	// 파일이 열리지 않았다면
	if(fd == -1)
	{
		// Open이라는 에러 출력
		perror("Open");
		// 강제 종료	
		exit(1);
	}
	//파일에 쓰기 수행
	n = write(fd, str, strlen(str));
	//만약 파일을 str의 바이트만큼 쓰지 않았다면 오류 출력
	if(n != strlen(str))
	{
		perror("Write");
		exit(1);
	}	

	close(fd);
	
	return 0;
}
