#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() 
{
     	int shmid;
        pid_t pid;
        char* addr1, *addr2;
        
	// 공유 메모리 생성.
	shmid = shmget(IPC_PRIVATE,20,IPC_CREAT|0644);
	
	// 공유 메모리 생성에 오류가 났다면
	if (shmid == -1)
	{
		// 에러를 출력하고 종료한다.
        	perror("shmget");
        	exit(1);
    	}

	// fork로 프로세스 생성.
        switch (pid = fork()) 
        {
		// fork가 실패한 경우
            	case -1 :
			perror("fork");
                    	exit(1);
                    	break;
		// 자식프로세스의 동작
            	case 0 :
			// 공유메모리를 연결하기
			addr1 = (char *)shmat(shmid, (char*)NULL,0);
                    	printf("=Child begins\n");
			// addr1에 작성하기
			sprintf(addr1,"Message from %d",getpid());
			printf("=Child ends\n");
                    	// 공유메모리 연결 해제
			shmdt((char *) addr1);
			exit(0);
			break;
		// 부모의 동작
            	default :
			// 자식이 끝나길 기다린다.
                    	wait(0);
			// 공유메모리를 연결하기
			addr2 = (char *) shmat(shmid, (char *)NULL,0);
			printf("=Parent begins\n");
			// 공유메모리에서 받은것을 출력하기
			printf("%s\n",addr2);
			printf("=Parent ends\n");
			// 공유메모리 연결 해제
			shmdt((char *) addr2);
			// 공유메모리 삭제
			shmctl(shmid, IPC_RMID, (struct shmid_ds*)NULL);
			break;
        }
	return 0;
}
