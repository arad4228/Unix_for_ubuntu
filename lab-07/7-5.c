#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

int main(void)
{
	int pd1[2];
	int pd2[2];
	pid_t pid;

	char* str;
	char buf[BUFSIZ];
	
	int len, status;
	// 파이프 생성하기	
	if(pipe(pd1) == -1)
	{
		// 오류가 있다면 출력하고 종료
		perror("Pipe Error");
		exit(1);
	}
	if(pipe(pd2) == -1)
	{
		// 오류가 있다면 출력하고 종료
		perror("Pipe Error");
		exit(1);
	}
	
	switch(pid = fork())
	{
		// 오류의 상황에서는 오류를 출력하고 종료
		case -1:
			perror("fork Error");
			exit(1);
			break;
		// 자식 프로세스의 동작
		case 0:
			// 자식은 pd1[0]을 읽을 것이므로 나머지는 종료
			close(pd1[1]);
			// 자식은 pd2[1]를 쓸 것이므로 나머지는 종료
			close(pd2[0]);
			//부모가 파이프로 보낸 정보를 읽어온다.
			len = read(pd1[0], buf, BUFSIZ);
			write(1,"Child Process Read:",19);
			write(1,buf, len);
			// 파이프에 정보를 쓴다.
			str = "From child\n";
			write(pd2[1], str, strlen(str));
			break;			
		default:
			// 부모는 pd1[0]을 쓸 것이므로 나머지는 종료
			close(pd1[0]);
			// 부모는 pd2[1]을 읽을 것이므로 나머지는 정리
			close(pd2[1]);
			// 부모쪽에서 pipe에보낼 데이터 작성
			str = "From parent\n"; 
			write(pd1[1], str, strlen(str));
			// 부모쪽에서 자식이 보낸 데이터 읽기
			len = read(pd2[0], buf,BUFSIZ);
			write(1,"Parent Process Read:",20);
			write(1,buf,strlen(buf));
			// 자식이 끝나길 대기
			waitpid(pid,&status,0);
			break;
	}	
	// 파이프 닫기
	close(pd1[0]);
	close(pd1[1]);
	close(pd2[0]);
	close(pd2[1]);
	
	return 0;
}
