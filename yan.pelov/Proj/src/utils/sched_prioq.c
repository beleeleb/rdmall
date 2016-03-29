
#include "prio_q.h"
#include "sched_prioq.h"
#include<assert.h>
#include <unistd.h>
#include <time.h>
#include<stdio.h>

struct task
{
	void *funcparam;
	int (*funcptr)(void* funcparam);
};

struct schedule_element
{
	time_t next_run;
	time_t frequency;
	task_t* task;
};

struct scheduler
{
	task_list *sched;
	int stop_flag;
};


scheduler_t* create_sched()
{
	scheduler_t* new_scheduler =  (scheduler_t*)malloc(sizeof(scheduler_t));
	assert(new_scheduler);
	new_scheduler->sched = (task_list*)q_create();
	new_scheduler->stop_flag = 0;
	return new_scheduler;
}


void destroy_sched(scheduler_t* scheduler)
{
	size_t size = sched_size(scheduler);
	size_t i = 0;
	scheduler_element_t* temp_elem = NULL;



	for(i = 0; i<size; ++i)
	{
		temp_elem = q_top((queue_t*)scheduler->sched);
		free(temp_elem);
		scheduler->sched = (task_list*)q_dequeue((queue_t*)scheduler->sched);
	}

	free(scheduler);

}

int add_task(scheduler_t* scheduler, task_t* task, time_t frequency, task_id* id)
{
	scheduler_element_t* new_scheduler_element = NULL;
	new_scheduler_element = (scheduler_element_t*)malloc(sizeof(scheduler_element_t));

	new_scheduler_element->next_run = time(0) + frequency;
	new_scheduler_element->frequency = frequency;
	new_scheduler_element->task = task;

	scheduler->sched =(task_list*)q_enqueue((queue_t *)scheduler->sched,
				(q_data) new_scheduler_element, (qid_t*) id,
								new_scheduler_element->next_run);

	return 0;

}

int cancel_task(scheduler_t* scheduler, task_id id, task_t** task)
{

	scheduler_element_t* temp_elem = NULL;

	scheduler->sched = (task_list*)q_cancel((queue_t*)scheduler->sched
		, (qid_t) id,(q_data*) &temp_elem);
	printf("\nfreq %lu\n", temp_elem->frequency);
	*task = (temp_elem->task);

	free(temp_elem);

	if(!task)
	{
		return 1;
	}

	return 0;
}


size_t sched_size(scheduler_t* scheduler)
{
	return q_size((queue_t*)scheduler->sched);
}

int stop_sched(scheduler_t* scheduler)
{
	scheduler->stop_flag = 0;
	return 0;
}

int sched_empty(scheduler_t* scheduler)
{
	return q_empty((queue_t*) scheduler->sched);
}

void run_sched(scheduler_t* scheduler)

{
	time_t new_time = 0;
	/*task_id id_task = 0;*/
	scheduler_element_t* temp_elem = NULL;

	scheduler->stop_flag = 1;

	while(scheduler->stop_flag)
	{
		temp_elem = (scheduler_element_t*) q_top((queue_t*)scheduler->sched);

		if(temp_elem->next_run <= time(0))
		{
			(temp_elem->task->funcptr)(temp_elem->task->funcparam);
			new_time = temp_elem->frequency + time(0);
			temp_elem->next_run = new_time;
			scheduler->sched = (task_list*)q_update_top_priority
								((queue_t*)scheduler->sched , (size_t) new_time);
		}

		else
		{
			sleep(temp_elem->next_run - time(0));
		}

	}

}

task_t* make_task( int (*funcptr)(void* funcparam) ,void *funcparam)
{
    task_t * new=(task_t*) malloc (sizeof(task_t));
    assert(new);

    new->funcptr=funcptr;
    new->funcparam=funcparam;

    return new;
}


/*#include <time.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "prio_q.h"
#include "sched_prioq.h"

enum RET {SUCCESS = 0, FAIL = 1};

struct scheduler
{
	task_list *sched;
	int stop_flag;
}; 

struct task
{
	void *funcparam;
	int (*funcptr)(void* funcparam); 
};

struct schedule_element
{
	time_t next_run;
	time_t frequency;
	task_t* task;
};

scheduler_t* create_sched(void)
{
	scheduler_t* new_sched = NULL;
	new_sched = (scheduler_t*)malloc(sizeof(scheduler_t));
	assert(new_sched);
	memset(new_sched, 0, sizeof(scheduler_t));

	new_sched->sched = q_create();
	new_sched->stop_flag = 0;

	return new_sched;
}

task_t* make_task(int (*funcptr)(void*), void *funcparam)
{
	task_t* new_task = NULL;
	new_task = (task_t*)malloc(sizeof(task_t));
	assert(new_task);
	memset(new_task, 0, sizeof(task_t));

	new_task->funcparam = funcparam;
	new_task->funcptr = funcptr;

	return new_task;
}

void e_destroy(scheduler_t* s)
{
	assert(s);

	scheduler_element_t* elem = q_top(s->sched);
	task_t* free_task = elem->task;
	memset(free_task, 0, sizeof(task_t));
	free(free_task);
	free_task = NULL;
	memset(elem, 0, sizeof(scheduler_element_t));
	free(elem);
	elem = NULL;
}

void destroy_sched(scheduler_t* s)
{
	assert(s);

	while(!sched_empty(s))
	{
		e_destroy(s);
		s->sched = q_dequeue(s->sched);
	}

	free(s->sched);
	memset(s, 0, sizeof(scheduler_t));
	free(s);
	s = NULL;
	return;
}


int add_task(scheduler_t* s, task_t* task, time_t frequency, task_id* id)
{
	scheduler_element_t* new_e = NULL;

	new_e = (scheduler_element_t*)malloc(sizeof(scheduler_element_t));
	assert(new_e);
	memset(new_e, 0, sizeof(scheduler_element_t));
    
	new_e->frequency = frequency;
	new_e->next_run = time(0) + new_e->frequency;
	new_e->task = task;
    
    s->sched = q_enqueue(s->sched, new_e,id, new_e->next_run);

	return SUCCESS;
}


int cancel_task(scheduler_t* s, task_id id, task_t** task)
{	
	assert(s && task);

	scheduler_element_t* temp_e = NULL;
  
	s->sched = q_cancel(s->sched, id, (void**)&temp_e);

	if (NULL == temp_e) 
	{
		return FAIL;
	}
    
	*task = temp_e->task;

	free(temp_e);

	return SUCCESS;
}

void run_sched(scheduler_t* s)
{
	assert(s);

    if(sched_empty(s))
    {
        return;
    }
       
	scheduler_element_t* temp_e = NULL;
	task_t* temp_task = NULL;
	s->stop_flag = 0;

	while(!s->stop_flag)
	{
		temp_e = q_top(s->sched);
        
		temp_task = temp_e->task;


        
        if(temp_e->frequency==0)
        {
            temp_task->funcptr(temp_task->funcparam);
            
            s->sched = q_dequeue(s->sched);
        }
       
		if(temp_e->next_run <= time(0) && temp_e->frequency!=0 && s->stop_flag!=1)
		{
            temp_task->funcptr(temp_task->funcparam);

			
			if(s->stop_flag==1)
		    {
				s->sched = q_dequeue(s->sched);
				break;
		    }
            
            
			temp_e->next_run = time(0) + temp_e->frequency;

			s->sched = q_update_top_priority(s->sched, temp_e->next_run);
            
		}

		else 
		{
			sleep(temp_e->next_run - time(0));
		}

	}

	return;
}
   
int stop_sched(scheduler_t* s)
{
	assert(s);

	printf("FINITO!\n");
	s->stop_flag = 1;
	return SUCCESS;
}

size_t sched_size(scheduler_t* s)
{
	assert(s);

	return q_size(s->sched);
}

int sched_empty(scheduler_t* s)
{
	assert(s);
	
	return q_empty(s->sched);
}
*/
