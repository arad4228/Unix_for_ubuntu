#include <pwd.h>
#include <stdio.h>

int main(void) 
{
    	struct passwd *pw;
	// UID 정경재를 가지고 파일 열기
   	pw = getpwnam("jeong-gyeongjae");
    	
	// pw uid를 출력
	printf("UID : %d\n", (int)pw->pw_uid);
    	// pw name 출력
	printf("Name : %s\n", pw->pw_name);
	// pw directory 출력
	printf("Home Directory : %s\n", pw->pw_dir);
	// pw shell 출력
	printf("Shell : %s\n", pw->pw_shell);
    	return 0;
}
