/*
 * testbarrier.c
 *
 *  Created on: Jan 8, 2015
 *      Author: student
 */
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "dlist.h"

pthread_mutex_t mutex;
sem_t sem;
pthread_cond_t cond_var;
dlist_t * list;
void* prod_func(void* arg);
void* cons_func(void* arg);

int main()
{
	pthread_t thread_id[11];
	long id[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    list = dlist_create();

	pthread_mutex_init(&mutex, NULL);

	sem_init(&sem, 0, 0);

	pthread_cond_init (&cond_var, NULL);

	pthread_create(&thread_id[0], NULL,
				&prod_func, (void*)1000);

	int i;

	for(i = 1; i < 11; ++i)
	{
		pthread_create(&thread_id[i], NULL,
					&cons_func, (void*)id[i]);
	}

	pthread_join(thread_id[0], NULL);

	for(i = 0; i < 10; ++i)
	{
		sem_post(&sem);
	}

	for(i = 1; i < 11; ++i)
	{
		pthread_join(thread_id[i], NULL);
	}

	sem_destroy(&sem);
	pthread_cond_destroy(&cond_var);
	pthread_mutex_destroy(&mutex);

	return 0;
}

void* prod_func(void* arg)
{
	int i = 0, j = 0;

	for(j = 0; j < 2; ++j)
	{
        int val;
        sem_getvalue(&sem, &val);
        
        if(val == 10)
        {
            for(i = 0; i < 10; ++i)
            {
                sem_wait(&sem);
            }
        }
        pthread_cond_broadcast(&cond_var);
		pthread_mutex_lock(&mutex);
        dlist_push_front(list, (dl_data)((int)arg+j));

      
		/*pthread_cond_wait(&cond_var, &mutex);*/

		printf("signal received\n");

		

		printf("sem updated\n");

		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void* cons_func(void* arg)

{
   /*int val = 0;
   sem_getvalue(&sem, &val);

   if(val == 0)
   {
	   pthread_cond_signal(&cond_var);
   }*/

    while(1)
    {
    sem_post(&sem);
   pthread_cond_wait(&cond_var, &mutex);
   pthread_mutex_lock(&mutex);
   sem_post(&sem);
   printf("thread num: %d\tthread id: %ld\tdata: %d\n", (long)arg,pthread_self(), dlist_get_data(dlist_next(dlist_begin(list))));
   
   pthread_mutex_unlock(&mutex);
    }
  
	return NULL;
}

