#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Todolist.h"

#define SOCKET_NAME   "TodolistProject"

int main(void) 
{
    	int sd, len;
	// 반복문을 끝내기 위한 장치이며 사용자의 입력을 받아줄 변수
    	char command;
	char incom;

	struct sockaddr_un ser;
	
	// 소켓을 생성한다.
    	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
	{
		// 만약 오류가 발생하면 에러를 출력하고 종료
        	perror("socket");
        	exit(1);
    	}	
	
	// 메모리를 초기화 하고 설정값들을 복사한다.
    	memset((char *)&ser, '\0', sizeof(ser));
    	ser.sun_family = AF_UNIX;
	// 소켓 주소 구조체에 값 저장
    	strcpy(ser.sun_path, SOCKET_NAME);
    	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	// 서버와 연결을 요청한다.
    	if (connect(sd, (struct sockaddr *)&ser, len) < 0) 
	{
		// 서버와 접속이 실패했다면 오류를 출력후 종료
        	perror("connection error");
        	exit(1);
    	}
	printf("서버와 연결중 ....\n");
	while(1)
	{
		printf("원하는 메뉴를 고르세요.\n");
		printf("1. 할일 저장하기\n");
		printf("2. 할일 지우기\n");
		printf("3. 할일 출력하기(모두)\n");
		printf("4. 할일 출력하기(오늘)\n");
		printf("5. 종료(Q,q)\n"); 
		scanf("%c", &command);
		int clen = 2;

		// Q또는 q가 들어오면 데이터 송수신을 중단하고 종료한다.
		if((command == 'q') || (command == 'Q'))
		{

			// 서버에게 종료 메시지 보내기.
			if(send(sd,command,clen,0) == -1)
			{
				// 보내기 실패했다면 오류메시지를 띄우고 다시 메뉴 선택
				perror("send, reselecte please\n");
				continue;
			}
			break;
		}
		switch(command)
		{
			case 1:
				// 첫번째 명령어를 받았다면 내부에서 명령어를 c로 변경하여 서버로 전달
				incom = 'c';
				if(send(sd,incom,clen,0) == -1)
				{
					// 오류가 발생하면 출력후 처음부터 메뉴 선택
					perror("send error\n");
					continue;
				}
				Todo todo;
				int days;
				char tname[MAX];
				char tdesct[MAXLEN];
				printf("Todolist에 저장할 항목을 입력해주세요.\n");
				scanf("요일: %d", &days);
				scanf("이름(50글자이내): %s", tname);
				scanf("설명(256글자 이내): %s", tdesct);
				todo.Days = days;
				strcpy(todo.Name, tname);
				strcpy(todo.Descrition, tdesct);	
				break;
			case 2:
				// 2번째 명령어를 받았다면 내부에서 명령어를 d로 변경하여 서버로 전달
				incom = 'd';
				char dname[MAX];
				if(send(sd,incom,clen,0) == -1)
				{
					// 오류가 발생하면 출력후 처음부터 메뉴 선택
					perror("send error\n");
					continue;
				}
				printf("TOdolist에서 삭제할 일정이름을 입력하세요.");
				scanf("%s", dname);
				break;

			case 3:
				// 3번째 명령어를 받았다면 내부에서 명령어를 P로 변경하여 서버로 전달
				incom = 'P';
				if(send(sd,incom,clen,0) == -1)
				{
					// 오류가 발생하면 출력후 처음부터 메뉴 선택
					perror("send error\n");
					continue;
				}


				break;

			case 4:
				// 4번째 명령어를 받았다면 내부에서 명령어를 p로 변경하여 서버로 전달
				incom = 'p';
				if(send(sd,incom,clen,0) == -1)
				{
					// 오류가 발생하면 출력후 처음부터 메뉴 선택
					perror("send error\n");
					continue;
				}


				break;

			default:
				printf("잘못된 값을 입력하셨습니다. 다시입력해주세요\n");
				break;
		}

	}
    	close(sd);

    	return 0;
}

