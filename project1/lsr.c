#include "lsr.h"

int main(int argc, char* argv[])
{
	struct stat buf;
	const char* directory = NULL;
	// argc가 1 이상이라는 것은 뒤에 어떠한 형식이 있다는 뜻이다.
	if (argc == 2)
	{
		// 디렉토리의 자리에 맞는 형식이 온건지 확인
		lstat(argv[1], &buf);
		if (S_ISDIR(buf.st_mode))
		{
			directory = argv[1];
		}
		// 일반적인 파일이라면 출력후 종료
		else if(S_ISREG(buf.st_mode))
		{
			printf("%s\n", argv[1]);
			return 0;
		}
		// 그렇지 않으면 오류메시지 출력후 종료
		else
		{
			printf("%s: 파일 또는 피렉토리가 아닙니다.\n",argv[1]);
			return 0;
		}
		
	}
	// 현재 원하던 형식이 아닌 경우
	else if (argc > 2)
	{
		printf("지원하지 않는 명령어 형식입니다.\n");
		printf("지정된 형식인 lsr (dir)을 사용해 주십시오\n");
		perror("Not support");
		exit(1);
	}
	// ls -R을 출력
	lsrecurprint(directory);
	
	return 0;
}
