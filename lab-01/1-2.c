#include <unistd.h>
#include <stdio.h>

//errno의 전역변수정의
extern int errno;

int main(void)
{	
	//unix.txt의 파일에 접근이 가능하면 0, 불가능하면 -1을 리턴한다.
	if(access("unix.txt",F_OK) == -1)
		printf("errono=%d\n",errno);
	
	return 0;
}	
