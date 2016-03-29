/*
 * testbuf_mutex.c
 *
 *  Created on: Jan 8, 2015
 *      Author: student
 */


#include "ring_buf.h"
#include "buf_mutex.h"
#include <semaphore.h>
#include <stdio.h>
#include <pthread.h>

rbuf_t *mybuf;
pthread_mutex_t mutex;
sem_t sem1, sem2;
extern void print_rbuf(rbuf_t* rbuffer);
void* prod_func(void* arg);
void* cons_func(void* arg);

int main()
{
	pthread_t thread_id[6];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 1);

	mybuf = rbuf_create(10);


	pthread_create(&thread_id[2], NULL,
						&cons_func, NULL);
	pthread_create(&thread_id[3], NULL,
						&cons_func, NULL);
	pthread_create(&thread_id[4], NULL,
						&cons_func, NULL);
	pthread_create(&thread_id[5], NULL,
						&cons_func, NULL);

	pthread_create(&thread_id[0], NULL,
					&prod_func, NULL);
	pthread_create(&thread_id[1], NULL,
						&prod_func, NULL);



	pthread_join(thread_id[0], NULL);
	pthread_join(thread_id[1], NULL);

	sem_post(&sem1);
	sem_post(&sem1);
	sem_post(&sem1);
	sem_post(&sem1);

	pthread_join(thread_id[2], NULL);
	pthread_join(thread_id[3], NULL);
	pthread_join(thread_id[4], NULL);
	pthread_join(thread_id[5], NULL);

	print_rbuf(mybuf);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	pthread_mutex_destroy(&mutex);

	rbuf_destroy(mybuf);
	return 0;
}

void* prod_func(void* arg)
{
	int val;
	int i;

	for(i = 0; i < 10/* && rbuf_full()*/; ++i)
	{
		sem_wait(&sem2);
		pthread_mutex_lock(&mutex);

		rbuf_write(mybuf, (void*)i);

		pthread_mutex_unlock(&mutex);

		sem_getvalue(&sem1, &val);
		sem_post(&sem1);

		printf("data inserted: %d\t thread is: %ld sem: %d\n", i, pthread_self(), val);
	}

	return NULL;
}

void* cons_func(void* arg)
{
	int val;

	data_t data = NULL;

	while(1)
	{
		sem_getvalue(&sem1, &val);
		sem_wait(&sem1);

		pthread_mutex_lock(&mutex);


		if(rbuf_in_use(mybuf) != 0)
		{
			data = rbuf_read(mybuf);
			sem_post(&sem2);
			printf("thread %ld got data: %d sem: %d\n", pthread_self(), (int)data, val);
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
