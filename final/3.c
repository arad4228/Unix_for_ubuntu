#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N 100000000

unsigned int s  = 0;
pthread_mutex_t mutex;

void* c(void* data)
{
	int i;
	for(i = 0; i < N; i++)
	{
		// mutex_lock을 요청한다.
		pthread_mutex_lock(&mutex);
		// s를 1를 증가한다.
		s++;
		// mutex lock를 해제한다.
		pthread_mutex_unlock(&mutex);
	}	
	return NULL;
}

int main(void)
{
	// mutex 객체를 초기화한다.
	pthread_mutex_init(&mutex, NULL);
	// 쓰래드 2개의 변수 선언
	pthread_t t[2];
	int r;
	// 쓰래드 생성과 c라는 함수를 실행한다.
	r = pthread_create(&t[0], NULL, c, NULL);
	// 만약 생성에 오류가 있다면
	if (r)
	{
		// 에러를 출력후 종료
		perror("Thread create:");
		exit(1);
	}
	// 쓰래드 생성과 c라는 함수를 실행한다.
	r = pthread_create(&t[1], NULL, c, NULL);
	// 만약 생성에 오류가 있다면
	if (r)
	{
		// 에러를 출력하고 종료한다.
		perror("Thread create:");
		exit(2);
	}
	// 쓰래드의 종료상태를 기다린다.
	pthread_join(t[0], NULL);
	pthread_join(t[1], NULL);
	
	printf("%u\n", s);
	// mutex lock 해제
	pthread_mutex_destroy(&mutex);
	return 0;
}
