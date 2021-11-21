#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	//임시 파일이름의 템플릿
	char fname[] = "temp-XXXXXX";
	//파일에 넣을 문자
	char str[] = "test for str";
	int fd;
	
	// 임시  파일이름 생성
	fd = mkstemp(fname);
	// 해당 파일 생성
	write(fd, str, sizeof(str)-1);
	close(fd);
	// 파일 이름 출력
	printf("temp name is %s\n",fname);
	return 0;
}
