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
dlist_t* list;

void* prod_func(void* arg);
void* cons_func(void* arg);

int main()
{
	list = dlist_create();
	pthread_mutex_init(&mutex, NULL);
	sem_init(&sem, 0, 0);
	pthread_cond_init (&cond_var, NULL);

	pthread_t thread_id[11];

	long id[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	pthread_create(&thread_id[0], NULL,
				&prod_func, (void*)1000);

	int i;

	for(i = 1; i < 11; ++i)
	{
		pthread_create(&(thread_id[i]), NULL,
					&cons_func, (void*)id[i]);
	}

	pthread_join(thread_id[0], NULL);

	for(i = 1; i < 11; ++i)
	{
		pthread_join(thread_id[i], NULL);
	}

	sem_destroy(&sem);
	/*dlist_destory(list);*/
	pthread_cond_destroy(&cond_var);
	pthread_mutex_destroy(&mutex);
	printf("\n\n**** DONE ***\n");
	return 0;
}

void* prod_func(void* arg)
{
	int i = 0, j = 0;

	for(j = 0; j < 5; ++j)
	{

		for(i = 0; i < 10; ++i)
		{
			sem_wait(&sem);
		}

		printf("sem updated\n");

	pthread_mutex_lock(&mutex);

	if(!dlist_is_empty(list))
	{
		dlist_pop_front(list);
	}

	if(j < 4)
	{
		dlist_push_front(list, (dl_data)((int)arg + j));
	}

	pthread_cond_broadcast(&cond_var);

	printf("signal sent\n");
	pthread_mutex_unlock(&mutex);

	}
	return NULL;
}

void* cons_func(void* arg)

{
	while(1)

	{
		pthread_mutex_lock(&mutex);

		sem_post(&sem);

		pthread_cond_wait(&cond_var, &mutex);

		if(dlist_is_empty(list))
		{
			printf("finish\n");
			pthread_mutex_unlock(&mutex);
			return NULL;
		}

		void * data = dlist_get_data(dlist_next(dlist_begin(list)));
		printf("thread %ld \tthread id: %ld***data: %d\n", (long)arg, pthread_self(), (int)data);
		pthread_mutex_unlock(&mutex);

	}

	return NULL;
}


/*
#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include "dlist.h"

pthread_mutex_t mutex;
sem_t sem;
pthread_cond_t thread_flag_cv;
dlist_t* dlist;

void* prod4(void* arg);
void* cons4(void* arg);

#define CONSU_NUM 6

pthread_cond_t thread_flag_cv;
static void main_test4();

int main()
{
	main_test4();
	return 0;
}

static void main_test4()
{
     exe NO. 4 *************************************************************
        dlist = dlist_create ();
        pthread_mutex_init (&mutex, NULL);
        int ret = sem_init(&sem, 0, 0);

        if(ret==-1)
        {
            perror("sem_init");
        }

        ret = pthread_cond_init (&thread_flag_cv, NULL);

        if(ret==-1)
        {
            perror("pthread_cond_init");
        }

         creating the producers

        pthread_t thread_id;
        pthread_create (&thread_id, NULL, &prod4, NULL);

        sleep(2);

         creating the consumers
        pthread_t thread_id2;
        pthread_create (&thread_id2, NULL, &cons4, NULL);

        pthread_t thread_id3;
        pthread_create (&thread_id3, NULL, &cons4, NULL);

        pthread_t thread_id4;
        pthread_create (&thread_id4, NULL, &cons4, NULL);

        pthread_t thread_id5;
        pthread_create (&thread_id5, NULL, &cons4, NULL);

        pthread_t thread_id6;
        pthread_create (&thread_id6, NULL, &cons4, NULL);

        pthread_t thread_id7;
        pthread_create (&thread_id7, NULL, &cons4, NULL);



        sleep(20);
       pthread_join(thread_id, NULL);

        sem_post(&sem);
        sem_post(&sem);
        sem_post(&sem);
        sem_post(&sem);
        sleep(10);
        pthread_join(thread_id2, NULL);
        pthread_join(thread_id3, NULL);
        pthread_join(thread_id4, NULL);
        pthread_join(thread_id5, NULL);
        pthread_join(thread_id6, NULL);
        pthread_join(thread_id7, NULL);
        sem_destroy(&sem);
        dlist_destroy(dlist);
        printf("\n\n********************************************************************** DONE\n");
        return;
}

void* prod4 (void* unused)
{

    int i = 0;
    int j = 0;

    for ( ; i < 10; ++i)
    {
        j = CONSU_NUM+1;

        while(--j)
        {
            sem_wait(&sem);
        }

        if ( pthread_mutex_lock (&mutex) )            { perror ("Mlock: size"); return (NULL); }

        if(!dlist_is_empty(dlist))
        {
            dlist_pop_front (dlist);
        }

        printf("%d thread N. %lu\n", i, pthread_self());

        if(i < 9)
        {
            dlist_push_front (dlist, (void*)((long)i));
        }

        pthread_cond_broadcast(&thread_flag_cv);

        if ( pthread_mutex_unlock (&mutex) )        { perror ("Mlock: size"); return (NULL); }
    }

    return (NULL);
}

void* cons4 (void* unused)
{
    printf ("\t\t\t\t\t\t ***************** start: %ld\n",pthread_self());

    while (1)
    {

        if ( pthread_mutex_lock (&mutex) )         { perror ("Mlock: size"); return (NULL); }
        printf ("\t\t\t\t theard in function: %ld\n",pthread_self());

        sem_post(&sem);


        printf("\nbefore pthread_cond_wait\n");

        pthread_cond_wait (&thread_flag_cv, &mutex);
        printf("\t\t\tdlist_is_empty : %d",dlist_is_empty(dlist));
        if ( dlist_is_empty(dlist) )
        {
            printf ("\t\t\t\t\t\t ***************** end #1: %ld\n",pthread_self());
            if ( pthread_mutex_unlock (&mutex) ) { perror ("Mulock: size"); return (NULL); }
            break;
        }


        printf ("\t\t node data is: %ld theard is: %ld\n", (long)dlist_get_data(dlist_next(dlist_begin(dlist))), pthread_self());

        if ( pthread_mutex_unlock (&mutex) ) { perror ("Mulock: size"); return (NULL); }
        sleep(1);
    }

    printf ("\t\t\t\t\t\t ***************** end #2: %ld\n",pthread_self());

    return (NULL);
}

*/
