#include "cdlist.h"
#include "prio_q.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

typedef int (*cmp_func)(cdl_data, void *);

struct queue_element
{
	qid_t qid;
	q_data data; /*pointer to struct function*/
	size_t prio;
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

static queue_element_t* create_q_element(q_data data)
{
	queue_element_t* new_e = (queue_element_t*)malloc(sizeof(queue_element_t));
	assert(new_e);
	memset(new_e, 0, sizeof(queue_element_t));
	new_e->qid = get_next_id();
	new_e->data = data;
	new_e->prio = 0;
	return new_e;
}

queue_t* q_create(void)
{
	return cdlist_create_list();
	
}

static void e_destroy(queue_t* q)
{
	queue_element_t* elem = cdlist_get_data(q);
	memset(elem, 0, sizeof(queue_element_t));
	free(elem);
	elem = NULL;
}

void q_destroy(queue_t* q)
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

static queue_t* q_enqueue2 (queue_t *q, queue_element_t* new_element, size_t prio)
{
	queue_t* curr = NULL;
	 if(NULL == q)
    {
        return cdlist_push_back(q, (void*)new_element);
    }
    
    curr = cdlist_prev(cdlist_end(q));
    
    while(curr != cdlist_begin(q))
    {
        if((((queue_element_t*)cdlist_get_data(curr))->prio) == prio || 
        (((queue_element_t*)(cdlist_get_data(curr)))->prio) < prio)
        {
            cdlist_insert_after(curr, new_element);
            return q;
        }
        curr = cdlist_prev(curr);
    }
    
    if((((queue_element_t*)cdlist_get_data(curr))->prio) > prio)
    {
        return cdlist_insert_after(cdlist_prev(cdlist_begin(q)), new_element);
    }
    
    cdlist_insert_after(cdlist_begin(q), new_element);
    return q;

}

queue_t* q_enqueue (queue_t *q, q_data data, qid_t *id, size_t prio)
{
    
	queue_element_t* new_element = NULL;
	queue_t* curr = NULL;
	new_element = create_q_element(data);
	new_element->prio = prio;
	*id = new_element->qid;	
	
    
    if(NULL == q)
    {
        return cdlist_push_back(q, (void*)new_element);
    }
    
    curr = cdlist_prev(cdlist_end(q));
    
    while(curr != cdlist_begin(q))
    {
        if((((queue_element_t*)cdlist_get_data(curr))->prio) == prio || 
        (((queue_element_t*)(cdlist_get_data(curr)))->prio) < prio)
        {
            cdlist_insert_after(curr, new_element);
            return q;
        }
        curr = cdlist_prev(curr);
    }
    
    if((((queue_element_t*)cdlist_get_data(curr))->prio) > prio)
    {
        return cdlist_insert_after(cdlist_prev(cdlist_begin(q)), new_element);
    }
    
    cdlist_insert_after(cdlist_begin(q), new_element);
    return q;
}

queue_t* q_update_top_priority (queue_t *q , size_t new_prio )
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return 0;
	}
	
	queue_element_t* new = cdlist_get_data(q);
    
	new->prio = new_prio;

	q = q_enqueue2(q, new, new_prio);

	q = cdlist_pop_front(q);

	return q;
}

queue_t* q_update_priority_by_qid (queue_t *q , qid_t qid ,size_t new_prio )
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return NULL;
	}

    cmp_func new_f = &cmp_qid;

	queue_t* temp = NULL;

	temp = cdlist_find(cdlist_begin(q), cdlist_end(q), new_f, (qid_t*)qid);

	queue_element_t* temp_data = cdlist_get_data(temp);

	temp_data->prio = new_prio; 

	q = q_enqueue2(q, temp_data, new_prio);

	temp = cdlist_remove(temp);

	 
	  
	return q;
}

int q_empty(queue_t* q)
{
	return cdlist_is_empty(q);
}

extern void print_q(queue_t* q)
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
		printf("qid: %ld priority: %ld data: %ld\n",  new->qid, new->prio, (long int)new->data);
		temp = cdlist_next(temp);
	} while(temp != q);
}

queue_t* q_dequeue(queue_t* q)
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

q_data q_top(queue_t* q)
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return 0;
	}
	
	queue_element_t* new = cdlist_get_data(q);
    
	return new->data;
}

queue_t* q_cancel(queue_t* q, qid_t qid, q_data *result)
{
	if(cdlist_is_empty(q))
	{
		printf("No elements in list\n");
		return NULL;
	}

    cmp_func new_f = &cmp_qid;

	queue_t* temp = NULL;

	temp = cdlist_find(cdlist_begin(q), cdlist_end(q), new_f, (qid_t*)qid);

	queue_element_t* temp_data = cdlist_get_data(temp);

	queue_element_t* top_data =  cdlist_get_data(q);

	*result = temp_data->data;
    
	if(temp_data == top_data)
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

size_t q_size(queue_t* q)
{
	return cdlist_size(q);
}

