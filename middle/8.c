#include <time.h>
#include <stdio.h>

int main(void)
{
	struct tm* tm;
	time_t t;
	// 요일을 문자로 바꾸기 위한 배열
	char* days[7] = {"일","월","화","수","목","금","토"};
	
	// tm에 시간을 받아와 저장한다.
	time(&t);
	tm =localtime(&t);
	// year값은 1900부터 이므로 1900을 더한 값을 출력해야 현재의 년도가 나온다.
	// month 역시 0~11까지 이므로 +1을 해야한다.
	// 나머지는 정상적으로 출력하면 되지만 wday는 0~6의값으로 나오므로 배열을 통한 변환을 해준다.	
	printf("%d. %d. %d. (%s) %d:%d:%d %s\n", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday,
						days[tm->tm_wday], tm->tm_hour, tm->tm_min, tm->tm_sec,
						tm->tm_zone);
	return 0;
}
	

