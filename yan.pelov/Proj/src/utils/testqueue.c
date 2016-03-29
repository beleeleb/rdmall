#include <stdio.h>
#include "cdlist.h"
#include "queue.h"

extern void print_que(queue_t* q);

int main (int argc, char** argv, char** evmp)
{

	qid_t qid1 = 0;

	qid_t qid2 = 0;

	qid_t qid3 = 0;

	q_data* tmp = 0;
		
	queue_t* que1 = NULL;
		
	queue_t* que2 = NULL;

	queue_t* que3 = NULL;


	que1 = que_enqueue(que1, (q_data)100, &qid1);
	
	que1 = que_enqueue(que1, (q_data)200, &qid1);
	
	que1 = que_enqueue(que1, (q_data)300, &qid1);

	print_que(que1);	 
	
	que1 = que_dequeue(que1);

	que1 = que_dequeue(que1);

	print_que(que1);	 
	
	que2 = que_enqueue(que2, (q_data)400, &qid2);
	
	que2 = que_enqueue(que2, (q_data)500, &qid2);
	
	que2 = que_enqueue(que2, (q_data)600, &qid2);

	print_que(que2);	 
	
	que1 = que_append(que1, que2);

	print_que(que1);	

	que3 = que_enqueue(que3, (q_data)700, &qid3);
	
	que3 = que_enqueue(que3, (q_data)800, &qid3);

	que3 = que_enqueue(que3, (q_data)900, &qid3);
	

	que1 = que_merge(que1, que3);

	print_que(que1);
		
	que1 = que_cancel(que1, 3, tmp);

	que1 = que_cancel(que1, 7, tmp);
	
	print_que(que1);

	que_destroy(que1);
	

	return 0;
}
