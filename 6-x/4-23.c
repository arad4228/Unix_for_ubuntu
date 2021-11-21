#include <time.h>
#include <stdio.h>

int main(void)
{
	struct tm* tm;
	int n;
	time_t t;
	char buf[BUFSIZ];
	
	time(&t);
	tm = localtime(&t);
	
	strftime(buf, sizeof(buf), "%G년 %m월 %d일 %U주 %H:%M", tm);
	printf("%s\n",buf);
	
	return 0;
}
