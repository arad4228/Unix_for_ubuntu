#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// errno.h의 변수를 가져와사용한다.
extern int errno;

int main(void)
{
	char *err;
	
	if(access("linux.txt", R_OK) == -1)
	{
		// err이라는 문자열에 errnum에 맞는 문자열을 리턴
		err = strerror(errno);
		printf("오류: %s(linux.txt)\n", err);
		//프로그램을 종료
		exit(1);
	}
	return 0;
}
