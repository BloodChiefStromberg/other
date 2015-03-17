#include <pthread.h>
#include <stdio.h>

int thread_count = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t thread_count_mutex = PTHREAD_MUTEX_INITIALIZER;

void *printLots(void *nothing)
{
	pthread_mutex_lock(&thread_count_mutex);
	int mynumber = thread_count;
	thread_count++;
	pthread_mutex_unlock(&thread_count_mutex);

	printf(" (hello from thread %d!) ", mynumber);
	int i;
	pthread_mutex_lock(&mutex);
	for (i = 0; i < 100; i++)
	{
		printf("%d.%d ", mynumber, i);
	}
	pthread_mutex_unlock(&mutex);

	return NULL;	
}

int main()
{
	pthread_t threads[3];
	int i;
	for (i = 0; i < 3; i++)
	{
		if (!pthread_create(&threads[i], NULL, printLots, NULL))
			printf(" (Succesfully created pthread %d!) ", i);
		else
			printf(" (creating pthread %d failed) ", i);
	}

	//Bad form good sport! I should join all the threads I've created here
	//but nah
	for (i = 0; i < 3; i++)
		pthread_join(threads[i], 0);
	
	return 0;
}
