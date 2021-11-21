#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	// System함수의 인자를받을 공간과 디렉토리위치를 받을 변수를 선언
	int pdate;
	char* cwd;
	// 3이 입력되지 않으면 무한 반복한다.
	while(1)
	{
		int select;
		printf("1) pwd\n2) date\n3) quit\n#? ");
		scanf("%d",&select);
		// 입력 받은 값을 1이면 pwd, 2이면 date, 3이면 종료 나머지는 Invalid selection을 띄운다.
		switch(select)
		{
			case 1:
			cwd = getcwd(NULL,BUFSIZ);
			printf("%s\n",cwd);	
			break;
			
			case 2:
			pdate = system("date");
			break;
			
			case 3:
			return 0;
			break;
			
			default:
			printf("Invalid selection\n");
			
		}	

	}
	return 0;
}
