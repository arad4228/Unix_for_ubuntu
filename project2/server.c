#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "Todolist.h"

#define SOCKET_NAME		"TodolistProject"

void Create_table(sqlite3* db)
{
	sqlite3* db = db;
	int rc;
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

	char* query = "CREATE TABLE Lists (Days INT, Name TEXT PRIMARY KEY, Descrition TEXT);";
	
	rc = sqlite3_exec(db, query, 0, 0, &err_msg);
	
	// 명령어 실행이 실패했다면 standard err에 오류를 출력
	if( rc != SQLITE_OK)
        {
                fprintf(stderr, "테이블을 만드는데 실패했습니다.\n");
                fprintf(stderr, "SQL error: %s\n",err_msg);
                sqlite3_free(err_msg);
        }
}

char Selectall(void* NotUsed, int argc, char** argv, char**azColName)
{
	NotUsed = 0;


}


int main(void)
{
	sqlite3* db;
	sqlite3_stmt* res;
	
	struct sockaddr_un ser, cli;
    	int sd, nsd, len, clen;

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
	while(1)
	{
		char command;
		// 클라이언트가 보낸 메시지를 읽기
		if (recv(nsd, command, sizeof(command), 0) == -1)
		{
			// 오류가 발생했다면 다시 메시지 읽기.
			perror("recve error\n");
			continue;
		}
		// 만약 클라이언트에서 종료를 보냈다면 서버 종료
		if(strcmp(command, 'Q') || strcmp(command.'q'))
			break;
		if(command = 'c')
		{

		}

	}

	close(nsd);
    	close(sd);

	return 0;
}
