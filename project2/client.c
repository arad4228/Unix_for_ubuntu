#include "Todolist.h"

#define SOCKET_NAME   "TodolistProject"

int main(void) 
{
    	int sd, len;
	// 반복문을 끝내기 위한 장치이며 사용자의 입력을 받아줄 변수
	char incom[4];
	struct sockaddr_un ser;
	
	char command;
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

	printf("서버와 연결 중입니다.....\n");
	// 서버와 연결을 요청한다.
    	if (connect(sd, (struct sockaddr *)&ser, len) < 0) 
	{
		// 서버와 접속이 실패했다면 오류를 출력후 종료
        	perror("connection error");
        	exit(1);
    	}
	printf("서버 연결완료\n");
	while(1)
	{
		// 보내는 메시지 공간
		char Smsg[TotalMax];
		// 받는 메시지 공간
		char Rmsg[TotalMax];
		int numberofRow;
		printf("원하는 메뉴를 고르세요.\n");
		printf("1. 할일 저장하기(N)\n");
		printf("2. 할일 지우기(D)\n");
		printf("3. 할일 출력하기(모두)(A)\n");
		printf("4. 할일 출력하기(ID)(S)\n");
		printf("5. 종료(Q,q)\n"); 
		scanf(" %c", &command);
		// Q또는 q가 들어오면 데이터 송수신을 중단하고 종료한다.
		if((command == 'q') || (command == 'Q'))
		{

			strcpy(incom,"qq");
			// 서버에게 종료 메시지 보내기.
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 보내기 실패했다면 오류메시지를 띄우고 종료
				perror("send, reselecte please\n");
				exit(1);
			}
			break;
		}
		else if(command == 'N')
		{	
			int len;
			// 첫번째 명령어를 받았다면 내부에서 명령어를 cd로 변경하여 서버로 전달
			strcpy(incom,"cd");
			if(send(sd,incom,sizeof(incom),0) == -1)	
			{
				// 오류가 발생하면 출력
				printf("send error\n");
			}
			char days[MAX];
			char tname[MAX];
			char tdesct[MAXLEN];	
			printf("Todolist에 저장할 항목을 입력해주세요.\n");
			printf("날짜를 입력해주세요:");
			scanf("%s", days);
			printf("이름(50글자이내):");
			scanf("%s", tname);
			printf("설명(256글자이내)");
			scanf("%s", tdesct);
			
			len = strlen(days);
			days[len+1] = '\0';
			strcpy(Smsg, days);
			if(send(sd, Smsg,sizeof(Smsg), 0) == -1)
			{
				perror("send error1\n");
				exit(1);
			}

			len= strlen(tname);
			tname[len+1] = '\0';
			strcpy(Smsg,tname);
			// 데이터는 서버로 전달
			if(send(sd, Smsg,sizeof(Smsg),0) == -1)
			{
				// 오류발생시 종료.
				perror("send error2\n");
				exit(1);
			}
			
			len = strlen(tdesct);
			tdesct[len+1] = '\0';
			strcpy(Smsg, tdesct);
			if(send(sd,Smsg,sizeof(Smsg),0) == -1)
			{
				perror("send error3\n");
				exit(1);
			}
			
			if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
			{
				printf("recv fail\n");
				exit(1);
			}
			printf("%s\n",Rmsg);
		}
		else if(command == 'D')
		{
			int len;
			// 2번째 명령어를 받았다면 내부에서 명령어를 dd로 변경하여 서버로 전달
			strcpy(incom, "dd");
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 출력후 처음부터 메뉴 선택
				printf("send error\n");
			}
			printf("TOdolist에서 삭제할 일정ID을 입력하세요.");
			scanf("%s", Smsg);
			len = strlen(Smsg);
			Smsg[len+1] = '\0';

			// 서버로 이름을 보내서 내용을 제거하기
			if(send(sd, Smsg,sizeof(Smsg),0) == -1)
			{	// 오류가 발생하면 출력 후 처음부터 시작
				printf("send error\n");
			}
			if(recv(sd, Rmsg, sizeof(Rmsg), 0) == -1)
			{
				printf("recv error\n");
				exit(1);
			}
			printf("%s\n",Rmsg);
	
		}
		else if(command == 'A')
		{	
			// 3번째 명령어를 받았다면 내부에서 명령어를 Pd로 변경하여 서버로 전달
			strcpy(incom, "Pd");
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 출력후 처음부터 메뉴 선택
				printf("send error\n");
			}

			// 몇개의 row인지 전송받음.
			if(recv(sd, Rmsg,sizeof(Rmsg),0) == -1)
			{
				printf("recv error\n");
			}
			numberofRow = atoi(Rmsg);
			printf("%d\n",numberofRow);
			if (numberofRow == 0)
			{
				printf("데이터베이스에 아무것도 없습니다.\n");
			}
			for(int i = 0; i < numberofRow; i++)
			{
				if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
				{
					printf("recv error\n");
					exit(1);
				}
				printf("%s\n",Rmsg);
			}
		}
		else if(command == 'S')
		{
			// 4번째 명령어를 받았다면 내부에서 명령어를 pd로 변경하여 서버로 전달
			strcpy(incom, "pd");
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 출력후 처음부터 메뉴 선택
				printf("send error\n");
			}
			printf("Todolist에서 출력하길 원하는 Id을 입력하세요.");
			scanf("%s", Smsg);
		
			// 삭제할 이름을서버로 보낸다
			if(send(sd, Smsg, sizeof(Smsg),0) == -1)
			{
				// 문제가 있다면 출력.
				printf("send error\n");
			}

			if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
			{
				printf("recv erro\n");
			}
			printf("%s\n",Rmsg);
		}
		else
		{
			printf("잘못된 값을 입력하셨습니다. 다시입력해주세요\n");
		}
	}
    	return 0;
}

