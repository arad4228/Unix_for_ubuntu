#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int fd;
	//3-1.txt라는 텍스트 파일을 열기 하지만 O_CREAT로 인해 없으면 파일을
	//생성하고 연다. open하는 모든 644이다. 
	fd = open("3-1.txt", O_CREAT, 0644);
	//파일이 열리지 않았다면 에러를 출력
	if(fd == -1)
	{
		perror("Open");
	}
	
	printf("fd is %d\n", fd);
	//파일을 닫는다.
	close(fd);

	return 0;
}
