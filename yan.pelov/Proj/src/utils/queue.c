#include "cdlist.h"
#include "queue.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef int (*cmp_func)(cdl_data, void *);

struct queue_element 
{
	qid_t qid;
	q_data data;
}; 

static qid_t get_next_id(void)
{
	static qid_t counter = 0;
	return ++counter;
}

int cmp_qid(cdl_data data, void* num)
{
	queue_element_t* tmp_e = data;
	return (tmp_e->qid==(qid_t)num);
}

queue_t* que_create(void)
{
	return cdlist_create_list();

}

static queue_element_t* create_q_element(q_data data)
{
	queue_element_t* new_e = (queue_element_t*)malloc(sizeof(queue_element_t));
	assert(new_e);
	memset(new_e, 0, sizeof(queue_element_t));
	new_e->qid = get_next_id();
	new_e->data = data; 
	return new_e;
}



static void e_destroy(queue_t* q)
{
	queue_element_t* elem = cdlist_get_data(q);
	memset(elem, 0, sizeof(queue_element_t)); 
	free(elem);
	elem = NULL;
}

void que_destroy(queue_t* q)
{
	if(cdlist_is_empty(q))
	{
		printf("Nothing to destroy\n");
		return;
	}

	queue_t* temp = q;
	
	do 									
	{
		e_destroy(temp);
		temp = cdlist_next(temp); 
	} while(temp != q);           
	
	cdlist_destroy(q);
	q = NULL;
}


queue_t* que_enqueue (queue_t* q, q_data data, qid_t *id )
{
	queue_element_t* new_e = create_q_element(data);
	q = cdlist_push_back(q, new_e);
	*id = new_e->qid;
	return q;
}

int que_empty(queue_t* q)
{
	return cdlist_is_empty(q); 
}

extern void print_que(queue_t* q)
{
	
	queue_t* temp = q;
	
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return;
	}
	
	do 									
	{
		queue_element_t* new = cdlist_get_data(temp);
		printf("qid: %ld data: %ld\n",  new->qid, (long int)new->data);
		temp = cdlist_next(temp);
	} while(temp != q);
}



queue_t* que_dequeue(queue_t* q)
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return NULL;
	}

	e_destroy(q);
	q = cdlist_pop_front(q);
	return q;
}

q_data que_top(queue_t* q)
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return 0;
	}
	
	queue_element_t* new = cdlist_get_data(q);

	return new->data;
}

static qid_t q_qid(queue_t* q) 
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return 0;
	}
	
	queue_element_t* new = cdlist_get_data(q);

	return new->qid;
}

queue_t* que_cancel(queue_t* q, qid_t qid, q_data *result)
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return NULL;
	}

	cmp_func new_f = &cmp_qid;

	queue_t* temp = NULL;

	temp = cdlist_find(cdlist_begin(q), cdlist_end(q), new_f, (qid_t*)qid);

	*result = que_top(temp);
	
	if(que_top(q) == result)
	{
		q = cdlist_next(q);
		e_destroy(temp);

		cdlist_remove(temp);

		return q;
	
	}
	
	e_destroy(temp);

	cdlist_remove(temp);

	return q;
}

size_t que_size(queue_t* q)
{
	return cdlist_size(q);
}



queue_t* que_append(queue_t* dest_q, queue_t* append_q)
{
	queue_element_t* new = NULL;
	if(cdlist_is_empty(dest_q))
	{
		return append_q;
	}

	while(!cdlist_is_empty(append_q))
	{
		new = cdlist_get_data(append_q);
		dest_q = cdlist_push_back(dest_q, new);
		append_q = cdlist_pop_front(append_q);
	}
	
	return dest_q;
	
	/*q_data temp_data = NULL; ****another possible way****
	qid_t temp_qid = 0;

	if(cdlist_is_empty(dest_q))
	{
		return append_q;
	}

	while(!cdlist_is_empty(append_q))
	{
		temp_data = q_top(append_q);
		temp_qid = q_qid(append_q);
		append_q = q_dequeue(append_q);
		dest_q = q_enqueue(dest_q, temp_data, &temp_qid);
	}

	return dest_q;*/
}

queue_t* que_merge(queue_t* dest_q, queue_t* merge_q)
{

	queue_element_t* new = NULL;
	queue_t* new_q = NULL;
	
	
	while(!cdlist_is_empty(merge_q) && (!cdlist_is_empty(dest_q)))
	{
		if(q_qid(dest_q) > q_qid(merge_q))
		{
			new = cdlist_get_data(merge_q);
			new_q = cdlist_insert_after(new_q, new);
			merge_q = cdlist_pop_front(merge_q);
		}
		
		if(q_qid(dest_q) < q_qid(merge_q))
		{
			new = cdlist_get_data(dest_q);
			new_q = cdlist_insert_after(new_q, new);
			
			dest_q = cdlist_pop_front(dest_q);
		}	

	}	
		
	while(!cdlist_is_empty(merge_q))
	{
		new = cdlist_get_data(merge_q);
		new_q = cdlist_insert_after(new_q, new);
		merge_q = cdlist_pop_front(merge_q);
	}
		
	while(!cdlist_is_empty(dest_q))
	{
		new = cdlist_get_data(dest_q);
		new_q = cdlist_insert_after(new_q, new);
		dest_q = cdlist_pop_front(dest_q);
		
	}
	
	return cdlist_next(new_q);
	
	

	
	/*q_data temp_data = NULL;   ****another possible way****
	qid_t temp_qid = 0;
	queue_t* new = NULL;

	if(q_size(merge_q)>q_size(dest_q))
	{
		printf("Error - dest_q is smaller than merge_q - merge_q was destroyed\n");
	q_destroy(merge_q);
		return dest_q;
	}
	
	while(!cdlist_is_empty(merge_q))
	{
		temp_data = q_top(dest_q);
		temp_qid = q_qid(dest_q);
		dest_q = q_dequeue(dest_q);
		new = q_enqueue(new, temp_data, &temp_qid);
		
		
		temp_data = q_top(merge_q);
		temp_qid = q_qid(merge_q);
		merge_q = q_dequeue(merge_q);
		new = q_enqueue(new, temp_data, &temp_qid);
	}
	
	while(!cdlist_is_empty(dest_q))
	{
		temp_data = q_top(dest_q);
		temp_qid = q_qid(dest_q);
		dest_q = q_dequeue(dest_q);
		new = q_enqueue(new, temp_data, &temp_qid);
	}
	return new;*/
}

