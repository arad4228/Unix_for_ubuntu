#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	// 만약 linux라는 폴더를 0755권한으로 생성에 실패했다면
	if(mkdir("linux", 0755) == -1)
	{
		//linux라는 에러를 띄우고 종료
		perror("linux");
		exit(1);
	}
	// 만약 programmingdlfksms 폴더를 0644권한으로 생성에 실패했다면
	if(mkdir("programming", 0644) == -1)
	{
		//programming이라는 에러를 출력하고 종료
		perror("programming");
		exit(1);
	}
	
	return 0;
}
