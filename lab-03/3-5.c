#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	FILE* rfp, * wfp;
	char buf[BUFSIZ];
	
	//파일을 읽기 전용으로 오픈
	// 실패했다면 오류 메시지 출력.
	if((rfp = fopen("3-1.txt", "r")) == NULL)
	{
		perror("fopen fail");
		exit(1);
	}
	
	//파일을 쓸기 전용으로 오픈 오픈시 안에있던 내용은 날라간다.
	// 실패시 오류 출력.
	if((wfp = fopen("3-5.txt", "w")) == NULL)
	{
		perror("fopen fail");
		exit(1);
	}
	
	// 문장단위로 읽고 넣는다.	
	while(fgets(buf,BUFSIZ,rfp) != NULL)
		fputs(buf, wfp);

	// 파일을 읽고 쓴 파일을 모두 닫는다.
	fclose(rfp);
	fclose(wfp);
	
	return 0;
}
