#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NUMLOOP 100000000

unsigned int cnt = 0;

void* count(void* data)
{
	int i;
	for(i = 0; i < NUMLOOP; i++)
		cnt++;
	return NULL;
}

int main(void)
{
	pthread_t t[2];
	int r;
	r = pthread_create(&t[0], NULL, count, NULL);
	if ( r != 0)
	{
		perror("Thread create:");
		exit(1);
	}	
	
	r = pthread_create(&t[1], NULL, count, NULL);
	if ( r != 0)
	{
		perror("Thread create:");
		exit(2);
	}	
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	
	printf("%u\n", cnt);
	return 0;
} 
