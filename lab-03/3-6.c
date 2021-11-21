#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char* fname;
	char fntmp[BUFSIZ];
	char template[32];
	
	//fname에 임시 파일명을 저장	
	fname = tmpnam(NULL);
	printf("1.TMP File Name(tmpnam) : %s\n", fname);
	
	//tmonam을 통해 임시 파일명을 생성
	tmpnam(fntmp);
	printf("2. TMP File Name(tmpnam) : %s\n", fntmp);
	
	//fname즉 임시파일명에 사용할 디렉토리를 지정
	fname = tempnam("/tmp", "coredump");
	printf("3.TMP File Name(tempnam) : %s\n", fname);
	
	//템플릿을 지정한 임시파일명 생성.
	strcpy(template, "/tmp/coredumpXXXXXX");
	fname = mktemp(template);
	printf("4. TMP File Name(mktemp) : %s\n", fname);

	return 0;
}
