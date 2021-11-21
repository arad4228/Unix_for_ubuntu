#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	//linux.txt파일에 접근 가능하면 0 불가능은 -1 리턴
	if(access("linux.txt",R_OK) == -1)
	{
		//오류에 대해 출력
		perror("linux.txt");
		exit(1);
	}
	return 0;
}
