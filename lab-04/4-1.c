#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(void)
{
	struct stat buf;
	
	//password.txt에 대한 정보 검색
	stat("password.txt", &buf);
	
	//해당 파일에 대한 inode정보들을 출력
	//inode 정보
	printf("Inode = %d\n",(int)buf.st_ino);
	// mode 정보(읽기 쓰기관련 정보들)
	printf("Mode = %o\n", (unsigned int)buf.st_mode);
	// haed link의 갯수
	printf("Nlink = %o\n",(unsigned int)buf.st_nlink);
	// 소유자
	printf("UID = %d\n", (int)buf.st_uid);
	// 소유 그룹
	printf("GID = %d\n", (int)buf.st_gid);
	// 파일 크기
	printf("SIZE = %d\n", (int)buf.st_size);	
	// 파일에 마지막 접근시간
	printf("Atime = %d\n", (int)buf.st_atime);
	// 파일이 마지막으로 modified된 시간
	printf("Mtime = %d\n",(int)buf.st_mtime);	
	// 마지막으로 변경된 시간
	printf("Ctime = %d\n", (int)buf.st_ctime);
	// block size
	printf("Bliksize = %d\n", (int)buf.st_blksize);
	// block의 갯수
	printf("Blocks = %d\n", (int)buf.st_blocks);
	
	return 0;
}
