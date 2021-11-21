#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
	
int main(void)
{
	FILE* fp ;
	int fd;
	char str[BUFSIZ];
	
	fd = open("unix.txt", O_RDONLY);
	if(fd == -1)
	{
		perror("Open");
		exit(1);
	}	
	
	fp = fdopen(fd,"r");
	
	fgets(str,BUFSIZ, fp);
	printf("%s\n", str);
	
	fclose(fp);
	return 0;
}
