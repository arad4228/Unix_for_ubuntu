#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	pid_t pid;
	// 명령어를 저장할 공간
	char* a[3];
	
	// 자식 프로세스를 생성
	if((pid = fork()) < 0)
	{
		// 만약 실패 했다면 fork 오류문을 띄우고 종료.
		perror("fork");
		exit(1);
	}	
	// 부모 프로세스의 동작
	if(pid > 0)
	{	
		// 해당 구문을 찍고 아무것도 하지 않는다.
		printf("Parent %d executes.\n", (int)getpid());
	}
	// 자식 프로세스의 동작
	else
	{
		// 해당 출력문을 찍고 명령어를 저장할 공간에 명령어를 삽입.
		printf("Child %d executes.\n", (int)getpid());
		a[0] = "ls"; // 실행 파일명
		a[1] = "-a";
		a[2] = NULL; // 인자의 끝을 나타내는 NULL포인
		// 실행할 경로를 /bin/ls로 설정하고 프로세스의 메모리 이미지를 변경. 
		if (execv("/bin/ls",a) == -1)
		{
			// 실패했다면 오류를 발생하고 종료.
			perror("exec");
			exit(2);
		}

	}

	return 0;
}
