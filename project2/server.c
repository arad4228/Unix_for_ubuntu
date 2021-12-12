#include <sqlite3.h>
#include "Todolist.h"

#define SOCKET_NAME		"TodolistProject"

int main(void)
{
	sqlite3* db;
	int rc;
	sqlite3_stmt* res;
	int step;
	int no = 0;	
	struct sockaddr_un ser, cli;
    	int sd, nsd, len, clen;
	// 받는 메시지
	char Rmsg[TotalMax];
	// 보낼 메시지
	char Smsg[TotalMax];

	// socket 생성
    	if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) == -1) 
	{
		// 문제가 발생하면 에러를 출력후 종료
        	perror("socket");
        	exit(1);
    	}
	// 메모리 초기화 및 소켓 구조체에 값을 저장한다.
    	memset((char *)&ser, 0, sizeof(struct sockaddr_un));
    	ser.sun_family = AF_UNIX;
    	strcpy(ser.sun_path, SOCKET_NAME);
    	len = sizeof(ser.sun_family) + strlen(ser.sun_path);

	// 소켓기술자와 소켈 주소 구조체를 연결한다.
    	if (bind(sd, (struct sockaddr *)&ser, len)) 
	{
		// 오류가 발생하면 에러를 출력후 종료
        	perror("bind");
        	exit(1);
    	}

	printf("클라이언트 접속 대기\n");
	// 클라이언트의 접속을 대기한다.
    	if (listen(sd, 5) < 0) 
	{
		// 에러가 발생하면 에러를 출력후 종료
        	perror("listen");
        	exit(1);
    	}
	
	// 클라이언트의 접속을 수용한다.
    	if ((nsd = accept(sd, (struct sockaddr *)&cli, &clen)) == -1) 
	{
		// 에러가 발생하면 오류를 출력후 종료
        	perror("accept");
        	exit(1);
    	}
	printf("클라이언트 접속 완료\n");
	// 데이터 베이스 생성
	char* err_msg = 0;

        // Todolist를 저장하는 database를 열기
        rc = sqlite3_open("Todolist.db", &db);
        // 해당 데이터 베이스를 연결 할 수 없다면
        if(rc !=  SQLITE_OK)
        {
                // standard error에 해당 메시지를 출력하고 프로그램을 종료한다.
                fprintf(stderr, "해당 데이터베이스를 열 수 없습니다. %s\n",sqlite3_errmsg(db));
                sqlite3_close(db);
                exit(1);
        }
        char* query = "DROP TABLE IF EXISTS Lists;"
                "CREATE TABLE Lists (ID INTEGER PRIMARY KEY, Name TEXT, Description TEXT);"
		"INSERT INTO Lists VALUES (1,'유닉스', '시험');";

        rc = sqlite3_exec(db, query, 0, 0, &err_msg);

        // 명령어 실행이 실패했다면 standard err에 오류를 출력
        if( rc != SQLITE_OK)
        {
                fprintf(stderr, "테이블을 만드는데 실패했습니다.\n");
                fprintf(stderr, "SQL error: %s\n",err_msg);
                sqlite3_free(err_msg);
        }
	
	while(1)
	{
		char command[4];
		// 클라이언트가 보낸 메시지를 읽기
		if (recv(nsd, command, sizeof(command), 0) == -1)
		{
			// 오류가 발생했다면 다시 메시지 읽기.
			perror("recve error\n");
			exit(1);
		}
		printf("%s\n", command);
		// 만약 클라이언트에서 종료를 보냈다면 서버 종료
		if(strcmp(command,"qq")== 0)
		{
			break;
		}
		// 데이터 집어넣기
		if(strcmp(command,"cd") == 0)
		{
			printf("ok cd\n");
			char Name[MAX];
			char Desct[MAXLEN];
			char* query = "INSERT INTO Lists(Name, Description) VALUES(?,?)";
			// client에서 보낸 메시지를 받기
			if(recv(nsd, Rmsg, sizeof(Rmsg), 0) == -1)
			{     
				// 오류가 발생하면 에러를 출력하고 다시 메시지 읽기
				perror("rece error\n");
				exit(1);
			}
			strcpy(Name,Rmsg);

			if(recv(nsd, Rmsg, sizeof(Rmsg), 0) == -1)
			{
				perror("recv2 error\n");
				exit(1);
			}
			strcpy(Desct, Rmsg);
			printf("%s %s\n",Name, Desct);

			rc = sqlite3_prepare_v2(db,query, -1, &res, 0);
			if( rc == SQLITE_OK)
			{
				sqlite3_bind_text(res,1,Name, -1, SQLITE_TRANSIENT);
				sqlite3_bind_text(res,2,Desct,-1, SQLITE_TRANSIENT);
				step = sqlite3_step(res);
				strcpy(Smsg,"저장이 완료되었습니다.\n");
                                if(send(nsd, Smsg, sizeof(Smsg),0) == -1)
                                {
                                        perror("send error\n");
                                        exit(1);
                                }

			}
			else
			{
				strcpy(Smsg, "저장에 실패했습니다\n");
				if(send(nsd, Smsg, sizeof(Smsg),0) == -1)
				{
					perror("send error\n");
					exit(1);
				}
			}
                        }
		// 데이터 삭제
		if(strcmp(command,"dd") == 0)
		{
			int id;
			printf("ok dd\n");
			if(recv(nsd, Rmsg, sizeof(Rmsg), 0) == -1)
			{
				perror("recve error\n");
				exit(1);
			}
			printf("%s\n",Rmsg);
			id = atoi(Rmsg);
			char* query = "DELETE FROM Lists WHERE ID = ?";
			rc = sqlite3_prepare_v2(db,query, -1, &res, 0);

			if( rc == SQLITE_OK)
			{
				sqlite3_bind_int(res,1,id);
			}
			step = sqlite3_step(res);
			strcpy(Smsg,"삭제가 완료되었습니다.\n");
			if( send(nsd,Smsg, sizeof(Smsg),0) == -1)
			{
				perror("send to fail");
				exit(1);
			}
			sqlite3_finalize(res);

		}
		// 데이터 모두 출력
		if (strcmp(command,"Pd") == 0)
		{
			printf("ok Pd\n");
			int count;
			char* query1 = "SELECT COUNT(Id) FROM Lists";
			rc = sqlite3_prepare_v2(db,query1,-1,&res,0);
			if(rc != SQLITE_OK)
			{
				perror("query error1\n");
				exit(1);
			}
			step = sqlite3_step(res);

			// 현재 몇개의 row가있는지 전송
			if(step == SQLITE_ROW)
			{
				sprintf(Smsg,"%d", sqlite3_column_int(res,0));
				count = atoi(Smsg);
				if(send(nsd,Smsg, sizeof(Smsg), 0) == -1)
				{
					perror("send error");
				}
			}

			sqlite3_finalize(res);

			// 모든 데이터를 전송하기.
			char* query2 = "SELECT * FROM Lists";
			rc = sqlite3_prepare_v2(db,query2,-1,&res,0);
			if(rc != SQLITE_OK)
			{
				perror("query error2\n");
				exit(1);
			}
			while(sqlite3_step(res) == SQLITE_ROW)
			{
				sprintf(Smsg,"ID: %d, 이름: %s, 세부내용: %s\n",
				sqlite3_column_int(res,0), sqlite3_column_text(res,1),
				sqlite3_column_text(res,2));
                                printf("%s",Smsg);
				if(send(nsd, Smsg, sizeof(Smsg),0) == -1)
                                        printf("send error\n");
			}

			sqlite3_finalize(res);
		}
		// Id으로 원하는 데이터 출력
		if (strcmp(command,"pd") == 0)
		{
			int id;
			printf("ok pd\n");
			if(recv(nsd,Rmsg,sizeof(Rmsg),0) == -1)
			{
				printf("rece error\n");
				exit(1);
			}
			id = atoi(Rmsg);
			printf("%s\n",Rmsg);
			char* query = "SELECT * FROM Lists WHERE ID = ?";
			rc = sqlite3_prepare_v2(db,query, -1, &res, 0);
			if( rc == SQLITE_OK)
			{
				sqlite3_bind_int(res,1,id);
			}
			step = sqlite3_step(res);

			if(step ==  SQLITE_ROW)
			{
				sprintf(Smsg,"ID: %d 이름: %s, 세부내용: %s\n",sqlite3_column_int(res,0), sqlite3_column_text(res,1),sqlite3_column_text(res,2));
				if(send(nsd, Smsg, sizeof(Smsg),0) == -1)
					printf("send error\n");
			}
			else
			{
				strcpy(Smsg,"아무런 데이터가 없습니다.");
				if(send(nsd, Smsg, sizeof(Smsg),0) == -1)
					printf("send erro\n");
			}
			sqlite3_finalize(res);
		}

	}

	sqlite3_close(db);
	close(nsd);
    	close(sd);

	return 0;
}
