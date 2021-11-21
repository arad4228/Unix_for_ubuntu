#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	// 만약 programming이라는 폴더를 제거하는 데 실패 했다면
	if(rmdir("programming") == -1)
	{
		// programming이라는 에러를 출력후 종료
		perror("programming");
		exit(1);
	}
	return 0;
}
