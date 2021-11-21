#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>


void lsprint(const char* directory);
// 멘처음에는 출력하지 않기에 이를 확인하기 위한 변수
bool first = true;

void lsrecurprint(const char* directory)
{
	// 넘어온 디렉토리 값이 없다면 현재 디렉토로리 설정한다.
	if (directory == NULL) 
	{
		// 현재의 디렉토리로 저장.
		directory = ".";
	}
	// 만약 현재의 디렉토리가 아니라면 디렉토리 이름을 출력
	if (first == false)
	{
		printf("%s:\n",directory);
	}
	// 만약 맨 첫번째 시작점이라면 디렉토리를 출력하지 않는다.
	if( first == true)
	{
		first = false;
	}
	// 디렉토리에 대한 정보 출력
	lsprint(directory);
	printf("\n");

	// Open a stream to loop through contents of directory and find any other
	// directories
	struct stat buf;
	struct dirent* d;
	DIR* dirStream = opendir(directory);

	// 해당 디렉토리에 파일 및 디렉토리 정보가 있는 동안
	while ((d = readdir(dirStream)) != NULL)
	{
		// 경로가 큰 경우를 대비해 전체 지렉토리 path를 10KB로 생성
		char concatDir[10240];
		// 메모리의 값을 0으로 초기화 한다.
		memset(&concatDir, 0, 10240);
		// 전체 디렉토리에 path에 현재 디렉토리를 복사
		strcpy(concatDir, directory);
		if (strcmp(directory, "/") != 0) 
		{
			// 전체 디렉토리 뒤에 '/'를 추가
			strcat(concatDir, "/");
		}
		// 전체 디렉토리에 하위 디렉토리의 이름을 붙인다.
		strcat(concatDir, (char* restrict)d->d_name);
		// concatDir의 정보를 받아올 수 있다면 
		if (lstat(concatDir, &buf) == 0) 
		{
			// 만약 해당 파일이 디렉토리라면 lsrecurprint를 호출한다.
			if (S_ISDIR(buf.st_mode)) 
			{
				// 그 디렉토리가 상위 폴더 및 하위 폴더를 가르키지 않으면 
				if (d->d_name[0] != '.') 
				{
					printf("\n");
					lsrecurprint(concatDir);
				}
			}
		}
	}
	closedir(dirStream);

	return;
}

void lsprint(const char* directory)
{
	struct dirent* d;
	struct stat buf;
	// 인자로 전달된 디렉토리의 정보가 없다면
	if (directory == NULL) 
	{
		// 현재 경로로 설정한다.
		directory = "."; 
	}
	// 해당 디렉토리를 열기.
	DIR* dirStream = opendir(directory);

	//열은 디렉토리에 파일 또는 디렉토리 정보가 있는 동안
	while((d = readdir(dirStream)) != NULL) 
	{
		// 경로가 큰 경우를 대비해 전체 지렉토리 path를 10KB로 생성
		char concatDir[10240];
		// 메모리의 값을 0으로 초기화 한다.
		memset(&concatDir, 0, 10240);
		// 전체 디렉토리에 path에 현재 디렉토리를 복사
		strcpy(concatDir, directory);
		if (strcmp(directory, "/") != 0) 
		{
			// 전체 디렉토리 뒤에 '/'를 추가
			strcat(concatDir, "/");
		}
		// 전체 디렉토리에 하위 디렉토리의 이름을 붙인다.
		strcat(concatDir, (char* restrict)d->d_name);
		// 해당 디렉토리의 이름이 '.' 아니라면		
		// 즉 하위 상위 디렉토리가 아니라면
		if (d->d_name[0] != '.') 		
		{	
			// directory에 대한 정보를 받아 올 수 있다면			
			if (lstat(concatDir, &buf) == 0) 
			{
				// 해당 내용을 출력
				printf("%s\t", d->d_name);			
			}
			// 그렇지 않다면
			else 			
			{
				printf("%s에 대한 정보를 읽을 수 없습니다.\n", d->d_name);
			}
		}
	}	
	closedir(dirStream);
	return;
}
