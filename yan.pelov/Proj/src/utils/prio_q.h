#ifndef __PRIO_Q_H__
#define __PRIO_Q_H__

#include <stdlib.h>
#include "prio_q_types.h"

/*typedef size_t qid_t;

typedef void*  q_data; 

typedef struct cdl_node queue_t;  

typedef struct queue_element queue_element_t; */

/*	Creates new queue
	Parameters: N/A. 
	Returns: Pointer to new queue.*/
queue_t* q_create(void);


/*	Destroys a given queue .
	Parameters:
 	 q: queue to destroy. 
	Returns: N/A */
void q_destroy(queue_t *q); 


/*	Push data to queue by priority.
	Parameters: 
	 q	 : pointer to queue
	 data: data to insert 
	 id : pointer to be assigned with id given to data - will be modified
	 prio: the priority of the element. (scale: 0 - 99, 0 is the highest priority).
	Returns: Pointer to queue. Must be assigned, might be modified */		
queue_t* q_enqueue (queue_t *q, q_data data, qid_t *id, size_t prio);


/*	update the priority (and location) of first element in the queue.
	Parameters: 
	 q	 : pointer to queue
	 new_prio: the priority to set.
	Returns: Pointer to queue. Must be assigned, might be modified  */			
queue_t* q_update_top_priority (queue_t *q , size_t new_prio );


/*	update the priority (and location) of first element in the queue.
	Parameters: 
	 q	 : pointer to queue
	 new_prio: the priority to set.
	Returns: Pointer to queue. Must be assigned, might be modified  */			
queue_t* q_update_priority_by_qid (queue_t *q , qid_t qid ,size_t new_prio );


/*	Removes next in queue in FIFO order.
	Parameters: 
	 q	 : pointer to queue
	Returns: Pointer to queue. Must be assigned, might be modified*/
queue_t* q_dequeue (queue_t *q);                                         


/*	Gets a copy of next in queue in FIFO order.
	Parameters: 
 	 q	 : pointer to queue
	Returns: A copy of data from first element in queue */ 
q_data q_top(queue_t *q);


/*	Removes a specific element from the queue by using its qid.
	Parameters: 
	 q	   : pointer to queue
	 qid   : id of an element in queue to be removed
	 result: pointer to be assigned with 
			 the canceled data -will be modified.
	Returns: Pointer to queue. Must be assigned, might be modified.
			result data with qid							*/
queue_t* q_cancel(queue_t *q, qid_t qid,q_data* result);


/*	Checks the number of elements in queue.
	Parameters: 
	 q	   : pointer to queue
	Returns: Number of elements in queue. */
size_t q_size(queue_t *q); 


/*	Checks if queue is empty.
	Parameters: 
	 q	   : pointer to queue
	Returns: TRUE/FALSE value. */
int q_empty(queue_t *q);


#endif /* __PRIO_Q_H__ */

