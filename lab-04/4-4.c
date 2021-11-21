#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;
	// password.txt에 대한 정보 검색
	stat("password.txt", &buf);
	// password.txt의 link 수를 출력
	printf("Link Count before link()= %d\n",(int)buf.st_nlink);	

	//password.txt에 대한 hard link 생성
	link("password.txt","password.ln");	

	// password.txt의 정보 검색
	stat("password.txt", &buf);
	// hard link후에 link의 수 출력.
	printf("Link Count after link()= %d\n", (int)buf.st_nlink);
	
	// hard link로 생성된 파일의 정보를 검색.
	stat("password.ln", &buf);
	printf("Link Count of password.ln= %d\n",(int)buf.st_nlink);

	// 심볼릭 링크 생성
	symlink("password.txt", "password.sln");
	
	// 다시 파일의 정보를 검색
	stat("password.txt", &buf);
	printf("Link Count of password.txt= %d\n", (int)buf.st_nlink);
	
	// 심볼릭 링크된 파일에 대한 정보 검색.
	stat("password.sln", &buf);
	printf("Link Count of password.sln= %d\n", (int)buf.st_nlink);
	
	// 심볼릭 링크 정보 검색
	lstat("password.sln", &buf);
	printf("Link Count of password.sln= %d\n", (int)buf.st_nlink);

	return 0;
}
