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
		printf("5. 오늘 할일출력하기(T)\n");
		printf("6. 종료(Q,q)\n"); 
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
			printf("프로그램 종료.\n");
			break;
		}
		else if((command == 'N') || (command == 'n'))
		{	
			int len;
			// 첫번째 명령어를 받았다면 내부에서 명령어를 cd로 변경하여 서버로 전달
			strcpy(incom,"cd");
			// 서버로 cd를 전달.
			if(send(sd,incom,sizeof(incom),0) == -1)	
			{
				// 오류가 발생하면 출력
				perror("send error\n");
			}
			// 서버로 전달할 인자들
			char days[MAX];
			char tname[MAX];
			char tdesct[MAXLEN];
			// 각 인자들에 대한 정보를 받습니다.	
			printf("Todolist에 저장할 항목을 입력해주세요.\n");
			printf("날짜를 입력해주세요:");
			scanf("%s", days);
			printf("이름(50글자이내):");
			scanf("%s", tname);
			printf("설명(256글자이내)");
			scanf("%s", tdesct);
			
			len = strlen(days);
			// 끝에 \0을 추가함으로 에러방지
			days[len+1] = '\0';
			strcpy(Smsg, days);
			// 날자에 대한 데이터를 서버로 전달
			if(send(sd, Smsg,sizeof(Smsg), 0) == -1)
			{
				perror("send error1\n");
				exit(1);
			}

			len= strlen(tname);
			// 끝에 \0을 추가함으로 에러 방지
			tname[len+1] = '\0';
			strcpy(Smsg,tname);
			// 이름의 데이터를 서버로 전달
			if(send(sd, Smsg,sizeof(Smsg),0) == -1)
			{
				// 오류발생시 종료.
				perror("send error2\n");
				exit(1);
			}
			
			len = strlen(tdesct);
			// 끝에 \0을 추가함으로써 에러방지
			tdesct[len+1] = '\0';
			strcpy(Smsg, tdesct);
			
			// 세부설명에 대한 데이터를 서버로 전달
			printf("서버로 데이터를 전달합니다....\n");
			if(send(sd,Smsg,sizeof(Smsg),0) == -1)
			{
				// 오류가나면출력후 종료
				perror("send error3\n");
				exit(1);
			}
			
			printf("서버로 전달이 완료되고 결과를 받는 중입니다....\n");
			// 서버로부터 받는 결과 메시지를 받는다.
			if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
			{
				// 오류발생시 출력후 종료
				printf("recv fail\n");
				exit(1);
			}
			// 추가에 대한 결과메시지를 출력한다.
			printf("%s\n",Rmsg);
		}
		else if((command == 'D') || (command == 'd'))
		{
			int len;
			// 2번째 명령어를 받았다면 내부에서 명령어를 dd로 변경하여 서버로 전달
			strcpy(incom, "dd");
			// 서버로 dd를 전달
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 출력후 종료
				printf("send error\n");
				exit(1);
			}

			printf("TOdolist에서 삭제할 일정ID을 입력하세요.");
			scanf("%s", Smsg);
			len = strlen(Smsg);
			// 에러를 방지하기 위해 \0을 넣는다.
			Smsg[len+1] = '\0';
			
			printf("서버로 데이터를 전달하는 중입니다....\n");
			// 서버로 이름을 보내서 내용을 제거하기
			if(send(sd, Smsg,sizeof(Smsg),0) == -1)
			{	// 오류가 발생하면 출력 후 종료.
				printf("send error\n");
				exit(1);
			}
			printf("서버로 데이터 전달이 완료되었고 서버로부터 데이터를 받는 중입니다...\n");
			// 서버로부터 데이터를 받는디.
			if(recv(sd, Rmsg, sizeof(Rmsg), 0) == -1)
			{
				printf("recv error\n");
				exit(1);
			}
			
			// 삭제 결과에 대해 출력
			printf("%s\n",Rmsg);
	
		}
		else if((command == 'A') || (command == 'a'))
		{	
			// 3번째 명령어를 받았다면 내부에서 명령어를 Pd로 변경하여 서버로 전달
			strcpy(incom, "Pd");
			// 서버로 Pd를 전달
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 출력후 처음부터 메뉴 선택
				printf("send error\n");
			}

			// 몇개의 row인지 전송받음.
			if(recv(sd, Rmsg,sizeof(Rmsg),0) == -1)
			{
				printf("recv error\n");
				exit(1);
			}
			
			// 전달받은 값을 int로 변환해서 저장
			numberofRow = atoi(Rmsg);
			
			// 만약 출력할 값이 없다면아래를 출력 그렇지 않으면
			if (numberofRow == 0)
			{
				printf("데이터베이스에 아무것도 없습니다.\n");
			}
			// row수만큼서버로 데이터를 받아 반복해서 출력을 한다.
			for(int i = 0; i < numberofRow; i++)
			{
				// 서버로부터 데이터를 전달받는다.
				if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
				{
					// 오류발생시 출력후 종료
					printf("recv error\n");
					exit(1);
				}
				printf("%s\n",Rmsg);
			}
		}
		else if((command == 'S') || (command == 's'))
		{
			// 4번째 명령어를 받았다면 내부에서 명령어를 pd로 변경하여 서버로 전달
			strcpy(incom, "pd");
			// 서버로 pd를 전달
			if(send(sd,incom,sizeof(incom),0) == -1)
			{
				// 오류가 발생하면 종료
				perror("send error\n");
				exit(1);
			}
			printf("Todolist에서 출력하길 원하는 Id을 입력하세요.");
			scanf("%s", Smsg);
			printf("서버로 데이터를 전달 중 입니다.\n");

			// 삭제할 id을서버로 보낸다
			if(send(sd, Smsg, sizeof(Smsg),0) == -1)
			{
				// 문제가 있다면 출력후 종료.
				perror("send error\n");
				exit(1);
			}
			
			printf("서버로 전달이 완료되었고 서버로부터 데이터를 받는중입니다....\n");
			// 서버로부터 삭제 결과에 대한 정보를 받는다.
			if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
			{
				// 오류발생시 출력후 종료
				perror("recv erro\n");
				exit(1);
			}
			printf("%s\n",Rmsg);
		}
		else if((command == 'T') || (command == 't'))
		{
			int numberofRow;
			// 5번째 명령어를 받았ㄲ다면 내부에서 명령어를 td로 변경하여 서버로 전달
			strcpy(incom, "td");
			// 서버에게 td를 전달
			if(send(sd, incom, sizeof(incom),0) == -1)
			{
				perror("send fail\n");
				exit(1);
			}

			printf("서버에서 데이터를 받아오는 중입니다.....\n");
			// 서버로부터 row의 갯수를 받아온다.
			if(recv(sd, Rmsg, sizeof(Rmsg), 0) == -1)
			{
				// 오류가 있다면 출력후 종료
				perror("recv error\n");
				exit(1);
			}
			numberofRow = atoi(Rmsg);
			
			// 출력할 값이 없다면 아래를 출력그렇지 않으면
			if( numberofRow == 0)
			{
				printf("오늘 해야할 일은 없습니다.\n");
			}
			// row의 갯수만큼 서버로부터 받아와 출력한다.
			else
			{
				for(int i =0; i < numberofRow; i++)
				{
					// 서버로부터 데이터를 받고 출력
					if(recv(sd, Rmsg, sizeof(Rmsg),0) == -1)
					{
						// 오류가 나면 출력후 종료
						perror("recv error\n");
						exit(1);
					}
					printf("%s\n",Rmsg);
				}
			}


		}
		// 모든 조건을 맞추지 않은 잘못입력한 경우
		else
		{
			printf("잘못된 값을 입력하셨습니다. 다시입력해주세요\n");
		}
	}
    	return 0;
}

