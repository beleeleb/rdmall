#ifndef __QUEUE_H__
#define __QUEUE_H__
#include <stdlib.h>

typedef cdl_iterator q_type; 

typedef size_t qid_t;

typedef void* q_data;

struct cdl_node;

typedef struct cdl_node queue_t;  

typedef struct queue_element queue_element_t; 

/*	Creates new queue
	Parameters: N/A. 
	Returns: Pointer to new queue.*/
queue_t* que_create(void);

/*	Destroys a given queue .
	Parameters:
 	 q: queue to destroy. 
	Returns: N/A */
void que_destroy(queue_t* q); 


/*	Push data to queue
	Parameters: 
	 q	 : pointer to queue
	 data: data to insert 
	 *id : pointer to be assigned with id given to data - will be modified
	Returns: Pointer to queue. Must be assigned, might be modified
			id given to data*/
queue_t* que_enqueue (queue_t* q, q_data data, qid_t *id );

/*	Removes next in queue in FIFO order.
	Parameters: 
	 q	 : pointer to queue
	Returns: Pointer to queue. Must be assigned, might be modified*/
queue_t* que_dequeue(queue_t* q);  

/*	Gets a copy of next in queue in FIFO order.
	Parameters: 
 	 q	 : pointer to queue
	Returns: A copy of data from first element in queue */ 
q_data que_top(queue_t* q);

/*	Removes a specific element from the queue by using its qid.
	Parameters: 
	 q	   : pointer to queue
	 qid   : id of an element in queue to be removed
	 result: pointer to be assigned with 
			 the canceled data -will be modified.
	Returns: Pointer to queue. Must be assigned, might be modified.
			result data with qid							*/
queue_t* que_cancel(queue_t* q, qid_t qid, q_data *result);

/*	Checks the number of elements in queue.
	Parameters: 
	 q	   : pointer to queue
	Returns: Number of elements in queue. */
size_t que_size(queue_t* q); 


/*	Checks if queue is empty.
	Parameters: 
	 q : pointer to queue
	Returns: TRUE/FALSE value. */
int que_empty(queue_t* q);

/*	Append two queues.
	Parameters: 
 	 dest_q: destination queue. 
 	 append_q: queue to append to destination queue.	 
	Returns: Pointer to destination queue. Must be assigned.*/	
queue_t* que_append(queue_t* dest_q, queue_t* append_q);  

/*	Merge two queues alternately.
	Parameters: 
 	 dest_q: destination queue. 
 	 merge_q: queue to merge with destination queue.	 
	Returns: Pointer to destination queue. Must be assigned.*/	
queue_t* que_merge(queue_t* dest_q, queue_t* merge_q);  

#endif /* __QUEUE_H__ */

