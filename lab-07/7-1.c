#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) 
{
    	int fd;
    	caddr_t addr;
    	struct stat statbuf;
	
	// 명령행 인자로 매핑할 파일이 없거나 많다면
    	if (argc != 2) 
	{
		// 오류를 출력하고 종료한다.
        	fprintf(stderr, "Usage : %s filename\n", argv[0]);
       		exit(1);
    	}
        // 기져온 명령행인자에 대한 정보를 받아 올 수 없다면
    	if (stat(argv[1], &statbuf) == -1) 
	{
		// 오류를 출력하고 종료
        	perror("stat");
        	exit(1);
    	}
	
	// 파일을 여는데 문제가 발생했다면 
    	if ((fd = open(argv[1], O_RDWR)) == -1) 
	{
		// 오류를 출력하고 종료
        	perror("open");
        	exit(1);
    	}
	
	// 파일 내용을 메모리에 매핑한다.
    	addr = mmap(NULL, statbuf.st_size, PROT_READ|PROT_WRITE,
                	MAP_SHARED, fd, (off_t)0);
    	// 만약 실패했다면
	if (addr == MAP_FAILED) 
	{
		// 오류를 출력하고 종료한다.
        	perror("mmap");
        	exit(1);
    	}
    	close(fd);
	
	// 메모리에 매핑 내용을 출력한다.
    	printf("%s", addr);

    	return 0;
}
