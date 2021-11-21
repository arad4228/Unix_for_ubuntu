#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	int fd, n;
	off_t start, cur;
	char buf[256];
	
	//파일 3-1.txt를 읽기 전용으로 열기
	fd = open("3-1.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Open 3-1.txt");
		exit(1);
	}
	//시작 오프셋을 현재에서 0만큼 이동 = 시작	
	start = lseek(fd, 0, SEEK_CUR);
	//에서 255만큼 읽는다.
	n = read(fd, buf, 255);
	
	//마지막에 '\0'삽입 문장으로 출력하기 위해.
	buf[n] = '\0';
	
	//해당 문장 출력
	printf("Offset start=%d, Read str=%s, n=%d\n", (int)start, buf, n);
	// 현재 위치에서 이동하지 않은 위치로 설정
	cur = lseek(fd, 0, SEEK_CUR);
	printf("Offser cur=%d\n",(int)cur);
	
	// 시작에서 7번째 위치로 변경
	start = lseek(fd, 7 ,SEEK_SET);
	// 해당위치에서 읽고 
	n = read(fd, buf, 255);
	// 문장 출력을 위한 삽입.
	buf[n] = '\0';
	printf("Offset start=%d, Read Str=%s\n", (int)start, buf);
	
	close(fd);
	
	return 0;
}
