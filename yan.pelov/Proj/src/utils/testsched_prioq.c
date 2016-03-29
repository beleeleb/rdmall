
#include "sched_prioq.h"
#include <stdio.h>


enum RET {SUCCESS = 0, FAIL = 1};
typedef int (*funcptr)(void* funcparam);

int print555(void* funcparam);

int print888(void* funcparam);

int print222(void* funcparam);

int print444(void* funcparam);

extern task_t* make_task(int (*funcptr)(void*), void *funcparam);

int add_me(void* funcparam);

int main(int argc, char **argv, char **epvm)
{
	scheduler_t* new_sched = NULL;
	funcptr f1 = &print555;
	funcptr f2 = &print888;
	funcptr f3 = &print222;

	task_t* task1 = NULL;
	task_t* task2 = NULL;
	task_t* task3 = NULL;
	task_t* task4 = NULL;
	task_t* task5 = NULL;
	task_t* empty_task = NULL;
	task_id id[7];
	
	new_sched = create_sched();

	task1 = make_task(f1, (void*)555);
	
	add_task(new_sched, task1, 3, &id[0]);

	task2 = make_task(f2, (void*)888);

	add_task(new_sched, task2, 2, &id[1]); 

	task3 = make_task(f3, (void*)222);

	add_task(new_sched, task3, 0, &id[2]); 

	task4 = make_task((funcptr)&stop_sched, new_sched); 
	
	add_task(new_sched, task4, 10, &id[3]); 

	cancel_task(new_sched, id[0], &empty_task); 

	cancel_task(new_sched, id[0], &empty_task); 

	add_task(new_sched, empty_task, 2, &id[4]);

	task5 = make_task((funcptr)&add_me, new_sched);  

	add_task(new_sched, task5, 2, &id[5]);

	run_sched(new_sched); 

	run_sched(new_sched); 

	destroy_sched(new_sched); 
	
	return SUCCESS;
}

int add_me(void* funcparam)
{
	task_id my_id = 0;
	task_t* new_task = make_task((funcptr)&print444, (void*)444);
	add_task(funcparam, new_task, 4, &my_id); 
	printf("I am add_me\n");
	return SUCCESS;	  
}

int print555(void* funcparam)
{
	printf("num: %ld\n", (long)funcparam);
	return SUCCESS;
}

int print888(void* funcparam)
{
	printf("num: %ld\n", (long)funcparam);
	return SUCCESS;
}

int print222(void* funcparam)
{
	printf("num: %ld\n", (long)funcparam);
	return SUCCESS;
}

int print444(void* funcparam)
{
	printf("num: %ld\n", (long)funcparam);
	return SUCCESS;
}



