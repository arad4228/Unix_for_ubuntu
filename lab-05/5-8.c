#include <stdio.h>
#include <sys/types.h>
#include <sys/times.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int i;
	struct tms tms5;
	clock_t t1, t2;
	// 시작 시간을 저장
	if((t1 = times(&tms5)) == -1)
	{	
		// 저장이 안됬다면 에러문구 출력후 종료
		perror("times 1");
		exit(1);
	}
	// 0부터 1000000까지 출력하는 부분	
	for(i = 0; i <= 1000000; i++)
		printf("%d\n",i);
	
	// 출력하는 부분을 마무리한 시간 저장
	if( (t2 = times(&tms5)) == -1)
	{
		// 저장이 안됬다면 에러문구를 출력후 종료
		perror("times 2");
		exit(1);
	}
	// 시간 출력
	printf("Real time : %.001f sec\n",(double)(t2-t1) / sysconf(_SC_CLK_TCK));
	printf("User time : %.001f sec\n",(double)tms5.tms_utime / sysconf(_SC_CLK_TCK));
	printf("System time ; %.001f sec\n",(double)tms5.tms_stime / sysconf(_SC_CLK_TCK));
	
	return 0;
}
