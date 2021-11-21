#include <time.h>
#include <stdio.h>

int main(void)
{
	struct tm* tm;
	time_t t;
	// MAC OS 형식
	char str1[BUFSIZ];
	// 실습 형식
	char str2[BUFSIZ];

	// 현재 시간 정보 가져오기
	time(&t);
	// time 객체에 정보 넣기
	tm = localtime(&t);	
	// 형식을 통한 변환
	strftime(str1, sizeof(str1), "%G년 %m월 %d일 %A %H시 %M분  %S초 %Z", tm);
	strftime(str2, sizeof(str2), "%G. %m. %d. (%A) %T %Z",tm);
	printf("MAC's OS time print\n");
	printf("%s\n",str1);
	printf("homework time print\n");
	printf("%s\n",str2);
	
	return 0;
}
