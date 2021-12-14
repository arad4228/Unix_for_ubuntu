#include <stdio.h>
#include <glib.h>
#include <string.h>

// 출력을 위한 함수
void print(gpointer data, gpointer userdata)
{
	printf("%s\t",(char*)data);
}

// 비교를 위한 함수로 alphabetic order에 사용한다.
gint compare1(gconstpointer a, gconstpointer b)
{
	return (gint) strcmp(*(const char**)a, *(const char**)b);
}

// 비교를 위한 함수로 reverse alphabertic order에 사용한다.
gint compare2(gconstpointer a, gconstpointer b)
{
	return (gint)strcmp(*(const char**)b, *(const char**)a);
}

int main(int argc, char* argv[])
{
	// queue를 위한 공간을 생성한다.
	GQueue* queue = g_queue_new();

	// queue에 값을 넣는다.
	for(int i = 1; i < argc; i++)
	{
		g_queue_push_head(queue, argv[i]);
	}
	
	printf("Queue Order\n");
	// queue 내부에 아무것도 없을 때까지 pop을 해서 출력한다.
	while(!g_queue_is_empty(queue))
	{
		printf("%s\t", (char * )g_queue_pop_tail(queue));
	}
	
	// 다시 queue에 원소를 집어넣는다 stack 출력을 위해	
	for(int i = 1; i < argc; i++)
	{
		g_queue_push_head(queue,argv[i]);
	}
	
	// 형식을 맞추기 위해 사용
	printf("\n");
	printf("\n");

	printf("Stack Order\n");
	// stack 형식으로 출력을 하는데 head에서 부터출력을 한다.
	while(!g_queue_is_empty(queue))
        {       
                printf("%s\t", (char * )g_queue_pop_head(queue));
        }
	// 형식을 맞추기 위해 사용
	printf("\n");
	printf("\n");
	
	// array를 생성한다.
	GPtrArray* array = g_ptr_array_new();

	// array에 값을 넣는다.
	for(int i = 1; i < argc; i++)
	{
		g_ptr_array_add(array, argv[i]);
	}
	
	// array에 있는 값을 compare1을 통해  정렬을 한다. 
	g_ptr_array_sort(array, compare1);
	printf("Alphabetical Order\n");
	// array의 내용을 출력하는 함수
	g_ptr_array_foreach(array, print, NULL);
	// 형식을 맞추기 위해 사용한다.
	printf("\n");
	printf("\n");

	// array에 있는 값을 comapare2를 통해  정렬을 한다.
	g_ptr_array_sort(array, compare2);
	printf("reverse Alphabetical Order\n");
	// array의 값을 출력한다.
	g_ptr_array_foreach(array, print, NULL);

	printf("\n");	
	return 0;
}
