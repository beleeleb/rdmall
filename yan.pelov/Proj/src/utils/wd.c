#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <assert.h>

#include "wd.h"
#include "sched_prioq.h"

/* struct defenitions */

struct handle
{
    pthread_t thread_id;
    pid_t wd_pid;
};

typedef struct sched_data
{
	char path[20];
	pid_t pid;
    
} sched_data_t;

/**********************/

int counter;

extern task_t* make_task(int (*funcptr)(void*), void *funcparam);

int func(void * arg);

void *sched_func(void * arg);

void reset_counter(int num, siginfo_t * info, void * data)
{
	counter = 0;
}

static int set_signal_handler(int signal , void(*handler_func)(int, siginfo_t *, void *) )
{
    struct sigaction act;
    memset (&act, '\0', sizeof(act));

    act.sa_sigaction = handler_func;
    act.sa_flags = SA_SIGINFO;

    if ( sigaction( signal , &act , NULL ) )
    {
        perror ("sigaction setting failed");
        return 1;
    }

    return 0;
}

handle_t* create_wd(void)
{
    handle_t* handle = (handle_t*)malloc(sizeof(handle_t));
    
    memset(handle, 0, sizeof(handle_t));
    
    sched_data_t *mydata = (sched_data_t *)malloc(sizeof(sched_data_t));
    memset(mydata, 0, sizeof(sched_data_t));
    
	pid_t pid;
    
    setenv("name1", "./testmyclient.out", 1);

	if(!getenv("is_wd"))
	{
        setenv("is_wd", "0", 1);
               
		pid = fork();
        
        if(pid < 0)
        {
            perror("fork error");
            return NULL;
        }
        
        if(pid == 0)
        {
            execlp("./testwd.out" ,"./testwd.out" , NULL);
        }
        
        else
        {
            mydata->pid = pid;
        }
	}
    
    else
    {
        mydata->pid = getppid();
    }

    strcpy(mydata->path, "./testwd.out");
    
    pthread_t id = {0};
    
    pthread_create(&id, NULL, &sched_func, (void*)mydata);
    
    /*pthread_join(id, NULL);*/
	
    
    handle->wd_pid = mydata ->pid;
    handle->thread_id = id;

	return handle;
}

void *sched_func(void * arg)
{
    assert(arg);

    set_signal_handler(SIGUSR1, &reset_counter);

	printf("threadId: %ld pid: %d path: %s\n", (long)pthread_self(), (int)((struct sched_data *)arg)->pid, ((struct sched_data *)arg)->path);

	scheduler_t* sched = create_sched();
        
	task_id id;
	task_t* task1 = make_task(&func, arg);
	add_task(sched, task1, 1, &id);

	run_sched(sched);
    
    destroy_sched(sched);

	return NULL;
}

int func(void * arg)
{
    assert(arg);
	printf("reskill: %d\n", kill(((struct sched_data *)arg)->pid, SIGUSR1));
	++counter;
	printf("mythread: %ld my pid: %d son_pid: %d counter: %d\n", (long)pthread_self(),(int)getpid(),(int)(((struct sched_data *)arg)->pid), counter);

    if(counter > 5)
	{
        counter = 0;
        
    	kill(((struct sched_data *)arg)->pid, SIGTERM);
    	wait(&(((struct sched_data *)arg)->pid));
        
    	pid_t pid;

    	pid = fork();

		if(pid < 0)
		{
			perror("fork error");
			return -1;
		}

		else if(pid == 0)
		{

			execlp(((struct sched_data *)arg)->path ,((struct sched_data *)arg)->path ,NULL);
		}

		else
		{
			((struct sched_data *)arg)->pid = pid;

		}
	}

	return 0;
}

void destroy_wd(handle_t* handle)
{
    kill(handle->wd_pid, SIGTERM);
    wait(&(handle->wd_pid));
    pthread_cancel(handle->thread_id);
    memset(handle, 0, sizeof(handle_t));
    free(handle);
    return;
}
