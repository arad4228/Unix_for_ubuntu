#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9000

int main(int argc, char* argv[]) 
{
    	int sd;
    	char msg[256];
    	struct sockaddr_in sin;
	
	// 메모리 초기화 및 소켓설정
    	memset((char *)&sin, '\0', sizeof(sin));
    	// TPC/IP 통신을 사용한다.
	sin.sin_family = AF_INET;
	// 포트번호를 연결
    	sin.sin_port = htons(PORTNUM);
	// localhost를 사용한다.
    	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 소켓을 생성한다.
    	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		// 만약 오류가 발생했다면  오류를 출력하고 종료
        	perror("socket");
        	exit(1);
    	}
	
	// 서버와 연결한다.
    	if (connect(sd, (struct sockaddr *)&sin, sizeof(sin))) 
	{	
		// 오류가 발생하면 출력하고 종료한다.
		perror("connect");
        	exit(1);
    	}
	// msg에 argv[1]의 값을 넣는다.
	sprintf(msg,"%s",argv[1]);
	for(int i =2; i<argc; i++)
	{
		// space를 위해 한칸 띄어 넣는다.
		// 즉 무조건 1칸이 띄어져있다고 생각한다.
		strcat(msg," ");
		// msg에 argv[i]을 연결한다.
		strcat(msg,argv[i]);
	}

	// 데이터를 서버에게 전송한다.
	if(send(sd, msg, sizeof(msg),0) == -1)
	{
		// 오류가 발생했다면 출력하고 종료한다.
		perror("send error");
		exit(1);
	}
				
	// 서버로부터 결과 데이터를 전달 받는다.
    	if (recv(sd, msg, sizeof(msg), 0) == -1) 
	{
		// 문제가 발생하면 출력하고 종료한다.
    		perror("recv");
    		exit(1);
    	}
	
	// 결과를 출력한다.
    	printf("From Server : %s\n", msg);
	
	// 소켓을 닫는다.
    	close(sd);

    	return 0;
}

