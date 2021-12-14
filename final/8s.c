#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PORTNUM 9000

int main(void) 
{
	char msg[256];
    	struct sockaddr_in sin, cli;
    	int sd, ns, clientlen = sizeof(cli);

	int len;	
	// 메모리를 초기화를 하고 소켓 구조체에 값을 저장한다.
    	memset((char *)&sin, '\0', sizeof(sin));
	// TCP 통신을 사용
    	sin.sin_family = AF_INET;
	// port 번호를 지정한다.
    	sin.sin_port = htons(PORTNUM);
	// local host로 값을 지정한다.
    	sin.sin_addr.s_addr = inet_addr("127.0.0.1");

	// 소켓을 생성한다.
    	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
        	perror("socket");
        	exit(1);
    	}
	
	//소켓 기술자와 소켓 주소 구조체를 연결한다.
    	if (bind(sd, (struct sockaddr *)&sin, sizeof(sin))) 
	{
		// 오류가 발생하면 출력하고 종료한다.
        	perror("bind");
        	exit(1);
    	}
	
	// 클라이언트의 접속요청을 대기한다.(최대 5명의 인원이 접속가능)
    	if (listen(sd, 5)) 
	{
		// 오류가 발생하면 출력하고 종료한다.
        	perror("listen");
        	exit(1);
    	}
	// 무한 반복
    	while (1) 
	{
		// 클라이언트의 연결 수용하기
        	if ((ns = accept(sd, (struct sockaddr *)&cli, &clientlen)) == -1) 
		{
            		perror("accept");
            		exit(1);
        	}
		// 클라이언트로부터 데이터를 받는다.	
		if( recv(ns, msg, sizeof(msg),0) ==  -1)
		{
			perror("recv error");
			exit(1);
		}
		// 받은 메시지의 글자를 확인한다.
		len = strlen(msg);
		// 받은 글자만큼 반복해서 대문자는 소문자로 소문자는 대문자로 변경한다.
		for(int i = 0; i<len; i++)
		{
			if(msg[i] >= 'A' && msg[i] <= 'Z')
				msg[i] = msg[i]+32;
			else if(msg[i] >= 'a' && msg[i] <= 'z')
				msg[i] = msg[i]-32;
		}
		
		// 클라이언트에게 변경된 값을 전송한다.
		if(send(ns, msg, strlen(msg),0) == -1)
		{
			perror("send error");
			exit(2);
		}
        	close(ns);
    	}
    	close(sd);

    	return 0;
}
