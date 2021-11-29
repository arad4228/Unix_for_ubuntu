#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wait.h>

int main(int argc, char *argv[]) 
{
        int fd;
        pid_t pid;
        caddr_t addr;
        struct stat statbuf;

        // 문자얄의 수가 2개 보다 많다먄
        if (argc != 2) 
        {
            //stadard err에 오류메시지를 출력하고 종료
            fprintf(stderr, "Usage : %s filename\n", argv[0]);
            exit(1);
        }

        // 기져온 명령행인자에 대한 정보를 받아 올 수 없다면
        if (stat(argv[1], &statbuf) == -1) 
        {
            // 오류를 출력하고 종료한다.
            perror("stat");
            exit(1);
        }

        // 파일을 여는 것에 대해 오류가 발생했다면 
        if ((fd = open(argv[1], O_RDWR)) == -1) 
        {
            // 오류를 출력하고 종료한다.
            perror("open");
            exit(1);
        }

        
        switch (pid = fork()) 
        {
		// fork가 실패한 경우
            	case -1 :
			perror("fork");
                    	exit(1);
                    	break;
		// 자식프로세스의 동작 mmap의 내용을 stdout으로 출력
            	case 0 :
                    	addr = mmap(NULL,statbuf.st_size, PROT_READ,MAP_SHARED,
			fd ,(off_t)0);
                    	write(1,addr,strlen(addr));
                    	break;
		// 부모의 동작 메모리 맵을 만들어 argv[1]에 해당하는 파일 매핑
            	default :
                    	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,
                    	MAP_SHARED, fd, (off_t)0);
                    	if (addr == MAP_FAILED) 
                    	{
                            	perror("mmap");
                            	exit(1);
                    	}
			wait(NULL);
			break;
        }
	close(fd);
	return 0;
}
