#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	
	DIR* dp;
	
	struct dirent* dent;
	
	// 만약 현재 디렉토리를 여는 것을 실패했다면 
	if((dp = opendir(".")) == NULL)
	{
		// opendir: .에러 메시지 출력 후 종료.
		perror("opendir: .");
		exit(1);
	}
	
	//현재 디렉토리의 정보를 읽는 동안
	while((dent = readdir(dp)))
	{	
		// 디렉토리의 정보들을 출력한다.
		printf("Name: %s ", dent->d_name);
		printf("Inode: %d\n", (int)dent->d_ino);
	}
	//디렉토리 닫기
	closedir(dp);
	
	return 0;
}
