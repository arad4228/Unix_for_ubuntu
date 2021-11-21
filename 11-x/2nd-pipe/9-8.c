#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int pd[2];
	char buf[BUFSIZ];
	
	pipe(pd);
	
	write(pd[1], "TEST STRING\n",12);
	read(pd[0], buf, 12);
	printf("%s", buf);
	
	return 0;
}
