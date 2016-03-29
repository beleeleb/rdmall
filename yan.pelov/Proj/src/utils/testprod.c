/*
 * testprod.c
 *
 *  Created on: Jan 8, 2015
 *      Author: student
 */
#include <pthread.h>
#include <prod.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include "dlist.h"

pthread_mutex_t mutex;
sem_t sem;
dlist_t* list;

int semid;
extern void dlist_print(dlist_t *head);

void* prod_func(void* arg)
{
	int val;
	int i;
	for(i = 0; i < 100; ++i)
	{
		pthread_mutex_lock(&mutex);

		dlist_push_front(list, (dl_data)i);

		pthread_mutex_unlock(&mutex);
		sem_getvalue(&sem, &val);
		sem_post(&sem);
		printf("data inserted: %d\t thread is: %ld sem: %d\n", i, pthread_self(), val);
	}
	return NULL;
}

void* cons_func(void* arg)
{
	int val;
	while(1)
	{
		sem_getvalue(&sem, &val);
		sem_wait(&sem);
		pthread_mutex_lock(&mutex);


		if(!dlist_is_empty(list))
		{
			int data = (int)(dlist_get_data(dlist_next(dlist_begin(list))));
			dlist_pop_front(list);
			printf("thread %ld got data: %d sem: %d\n", pthread_self(), data, val);

		}

		else
		{
			pthread_mutex_unlock(&mutex);
			return NULL;
		}


		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}


int main()
{
	pthread_t thread_id[6];
	pthread_mutex_init(&mutex, NULL);
	list = dlist_create();
	sem_init(&sem, 0, 0);

	pthread_create(&thread_id[0], NULL,
				&prod_func, NULL);

	pthread_create(&thread_id[1], NULL,
					&prod_func, NULL);

	pthread_create(&thread_id[2], NULL,
						&cons_func, NULL);

	pthread_create(&thread_id[3], NULL,
						&cons_func, NULL);

	pthread_create(&thread_id[4], NULL,
							&cons_func, NULL);

	pthread_create(&thread_id[5], NULL,
							&cons_func, NULL);

	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);
	sem_post(&sem);
			sem_post(&sem);
			sem_post(&sem);
			sem_post(&sem);

	pthread_join(thread_id[2], NULL);
	pthread_join(thread_id[3], NULL);
	pthread_join(thread_id[4], NULL);
	pthread_join(thread_id[5], NULL);
	dlist_print(list);
	sem_destroy(&sem);

	pthread_mutex_destroy(&mutex);
	return 0;
}
