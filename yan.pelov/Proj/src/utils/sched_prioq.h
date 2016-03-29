#ifndef __SCHED_PRIOQ_H__
#define __SCHED_PRIOQ_H__
#include "prio_q.h"
#include "sched_prioq_types.h"
#include <stdlib.h>

/*typedef struct scheduler scheduler_t;

typedef queue_t* task_list;

typedef struct schedule_element scheduler_element_t;

typedef struct task task_t;

typedef size_t task_id;*/

/*	Creates new scheduler
	Parameters: N/A. 
	Returns: Pointer to new scheduler.*/
scheduler_t* create_sched(void);

task_t* make_task(int (*funcptr)(void*), void *funcparam);

/*	Destroys a given scheduler.
	Parameters:
 	 scheduler: Pointer to scheduler.
	Returns: N/A */
void destroy_sched(scheduler_t* s); 

/*	Pushes a new task to the scheduler by priority.
	Parameters: 
	 scheduler_t: Pointer to scheduler.
	 task_t*: Task to be added.
	 time_t frequency: Cycle time of the task.
	 task_id*: Pointer for assignment of unique task id.
	Returns: SUCCESS or error code (error code list: -----   ) .
	*/	 
int add_task(scheduler_t* s, task_t* task, time_t frequency, task_id* id);

/*	Removes a specific task from the scheduler.
	Parameters: 
	 task_t: Pointer to task from canceled scheduler element.
	 task_id: ID of scheduler element to be removed.
	Returns: SUCCESS/FAIL value (in case requested element was not found). */
int cancel_task(scheduler_t* s, task_id id, task_t** task);

/*	Runs the scheduler.
	Parameters: 
 	 schedule: Pointer to scheduler.
	Returns: N/A */
void run_sched(scheduler_t* s);             

/*	stops the scheduler.
	Parameters: 
	 schedule: Pointer to scheduler.
	Returns: N/A		*/
int stop_sched(scheduler_t* s); 

/*	Checks number of functions in the scheduler.
	Parameters: 
	 schedule: Pointer to scheduler to be measured.
	Returns: Number of tasks.	 */
size_t sched_size(scheduler_t* s);

/*	Checks if scheduler is empty.
	Parameters: 
	 schedule: Pointer to scheduler to be checked.
	Returns: TRUE/FALSE value. */
int sched_empty(scheduler_t* s);

#endif 	/* __SCHED_PRIOQ_H__ */
