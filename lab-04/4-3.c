#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;
	// password.txt에 대한 정보 검색 .
	stat("password.txt", &buf);
	// 원래 password.txt의파일의 종류, 특수접근권한, 각종 사용자들의(읽기 쓰기 실행 권한에 대한 정보들)을 출력
	printf("mode before change = %o\n", (unsigned int)buf.st_mode);
	// 그룹의 쓰기 권한을 부여
	buf.st_mode |= S_IWGRP;
	// other의 읽기권한 해제
	buf.st_mode &= ~(S_IROTH);
	// 모드 변경
	chmod("password.txt",buf.st_mode);
	// 바뀌고 난다음의 모드 출력
	printf("mode after change = %o\n", (unsigned int)buf.st_mode);
	
	return 0;
}
