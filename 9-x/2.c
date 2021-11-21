#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

int g = 10;

void* tfunction(void* data)
{
	int d = *(int*)data;
	int tid = (int) pthread_self();
	int pid =(int)getpid;
	printf("Hello! I'm thread %u of %d, %d is passed from main\n", tid,pid,d);
	printf("external variable is %d\n", ++g);
	pthread_exit(NULL);
}

int main(void)
{
	pthread_t t1,t2;
	int rcc, t = 1;
	printf("In main: creating thread t1\n");
	rcc = pthread_create(&t1, NULL, tfunction, (void*) &t);
	if(rcc != 0)
	{
		printf("Thread creation error.\n");
		exit(1);
	}
	sleep(2);
	t++;
	printf("In main: creating thread t2\n");
	rcc = pthread_create(&t2, NULL, tfunction, (void*)&t);
	if(rcc != 0)
	{
		printf("THread creation error.\n");
		exit(2);
	}
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	return 0;
}
