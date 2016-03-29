#include "cdlist.h"
#include "prio_q.h"
#include <stdio.h>

extern void print_q(queue_t* q);

typedef int(*func)(void*);

struct function
{
	func p_func;
	void* p_param;
};

int main (int argc, char** argv, char** evmp)
{
	qid_t qid1 = 0;
      
	queue_t* que1 = NULL;

	queue_t* que2 = NULL;

	queue_t* que3 = NULL;

	q_data tmp = NULL;
       
	que1 = q_enqueue(que1, (q_data)100, &qid1, 5);

	que1 = q_enqueue(que1, (q_data)200, &qid1, 6);

	que1 = q_enqueue(que1, (q_data)100, &qid1, 7);

	que1 = q_enqueue(que1, (q_data)200, &qid1, 5);

	que1 = q_enqueue(que1, (q_data)200, &qid1, 3);

	que1 = q_enqueue(que1, (q_data)300, &qid1, 5);
	
	que1 = q_enqueue(que1, (q_data)200, &qid1, 8);
	
	que1 = q_enqueue(que1, (q_data)300, &qid1, 9);

	print_q(que1);
	   
	que1 = q_dequeue(que1);
    
	que1 = q_dequeue(que1);
    
	print_q(que1);
	
	que2 = q_enqueue(que2, (q_data)400, &qid1, 9);
	
	que2 = q_enqueue(que2, (q_data)500, &qid1, 2);
	
	que2 = q_enqueue(que2, (q_data)600, &qid1, 8);
    
	print_q(que2);
	        
	print_q(que1);  
    
	que3 = q_enqueue(que3, (q_data)700, &qid1,5);
	
	que3 = q_enqueue(que3, (q_data)800, &qid1,9);
    
	que3 = q_enqueue(que3, (q_data)900, &qid1,1);
    
	print_q(que1);
	
	que1 = q_cancel(que1, 3, &tmp);
	
	que1 = q_cancel(que1, 7, &tmp);
    
	print_q(que1);
    
	q_destroy(que1);
	
    
	return 0;
}
