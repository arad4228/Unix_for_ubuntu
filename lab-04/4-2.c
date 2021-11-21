#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;
	//password 파일에 대한 정보를 검색
	stat("password.txt", &buf);
	//password 파일의 종류, 특수접근권한 및 유저, 그룹, other의  읽기 쓰기 실행 모드 정보를 출력
	printf("Mode = %o (16진수: %x)\n",(unsigned int)buf.st_mode, (unsigned int)buf.st_mode);
	//password 파일이 FIFO파일인지 확인하는 메크로
	if(S_ISFIFO(buf.st_mode))
		printf("password.txt: FIFO\n");
	//password 파일이 디렉토리인지 확인하는 메크로
	if(S_ISDIR(buf.st_mode))
		printf("password.txt: Diretiry");
	//password 파일이 일반파일인지 확인하는 메크로
	if(S_ISREG(buf.st_mode))
		printf("password.txt: Regular File\n");
	
	return 0;
}
