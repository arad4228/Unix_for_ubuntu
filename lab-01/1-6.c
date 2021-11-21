#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char* str;
	
	// str의 공간을 동적할당을 해준다.
	//str = malloc(sizeof(char) * 20);
	
	// 동적할당된 str에 Hello를 복사해준다.
	strcpy(str,"Hello");
	// str == Hello를 출력한다.
	printf("%s\n", str);
	
	//동일한 작업 반복
	strcpy(str, "Good morning");
	printf("%s\n", str);
	
	// 동적할당된 메모리 해제
	free(str);
	return 0;
}
