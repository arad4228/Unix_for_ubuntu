#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g = 10;

void *tfunction(void *data)
{
	int id = *(int*) data;
	printf("Hello! I'm thread #%d, g = %d\n", id, ++g);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t t1;
	int rcc, t = 1;
	printf("In main: creating thread\n");
	rcc = pthread_create(&t1, NULL, tfunction, (void*)&t);
	if(rcc != 0)
	{
		printf("Thread creadtion error!\n");
		exit(1);
	}
	pthread_join(t1, NULL);
	return 0;
}
