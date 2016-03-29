#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "dlist.h"
#include "utils.h"
#include <stddef.h>

#define DUMMY_DATA 0xDEADBEEF  
 
typedef int (*func)(dl_data, void *);

/***********************function declarations*******************/

extern void dlist_print(dlist_t *head);
extern dl_iterator dlist_head(dlist_t* head);
int useless(dl_data data, void* num);

/********************end of function declaration****************/
func useless_func =&useless;

enum BOOLEAN
{
	FALSE = 0, TRUE = 1
};

enum RESULT
{
	SUCCESS = 0, FAIL = 1
};

struct dl_node
{
	dl_data *data;
	struct dl_node *prev;
	struct dl_node *next;
};

struct dlist

{
  dl_node_t *head;
  dl_node_t *tail;
};

/***********************************************************/

static dl_iterator iter_create(dl_data data)
{
	dl_iterator new_iter;
	
	new_iter = (dl_node_t*)malloc(sizeof(dl_node_t));
	assert(new_iter);
	memset(new_iter, 0, sizeof(dl_node_t));

	new_iter->data = data;

	return new_iter;
}

/***********************************************************/
void dlist_print(dlist_t *head)
{
	
	dl_iterator temp = NULL;

	temp = head->head;

	if(!(temp->next->next))
	{
		printf("No element in list\n");
		return;
	}


	while(temp)
	{
		if((unsigned int)temp->data == 0xDEADBEEF)
		{
			printf("DEADBEEF\n");
		}

		else printf("INSIDE: %u\n", (unsigned int)temp->data);

		temp = temp->next;	
	}
	
	return;
}

/***********************************************************/
extern dl_iterator dlist_head(dlist_t* head)
{
	assert(head);
	
	return (head->head);
}
/***********************************************************/

dl_data dlist_get_data(dl_iterator iter)
{
	if(!iter) return NULL;

	if((iter->next==NULL) || (iter->prev==NULL))
	{
		return NULL;
	}

	else return iter->data;
}

/***********************************************************/
dlist_t* dlist_create()
{
	dlist_t* new_list = NULL;
	
	new_list = (dlist_t*)malloc(sizeof(dlist_t));
	
	assert(new_list);
	
	memset(new_list, 0, sizeof(dlist_t));
	
	new_list->head = iter_create((dl_data)DUMMY_DATA);
	new_list->tail = iter_create((dl_data)DUMMY_DATA);
	
	new_list->head->next = new_list->tail;
	new_list->head->prev = NULL;
	
	new_list->tail->next = NULL;
	new_list->tail->prev = new_list->head;
	
	return new_list;
}

/***********************************************************/
void dlist_destroy(dlist_t* head)
{
	assert(head);
	
	/*return dlist_foreach(dlist_begin(head),dlist_end(head), useless_func, 0);*/
	
	dl_iterator temp_node = NULL;
	
	while(head->head)
	{
		temp_node = head->head;
		head->head = head->head->next;
		
		memset(temp_node, 0, sizeof(dl_node_t)); 
		
		free(temp_node);	
	}
	
	free(head);
}

/***********************************************************/
dl_iterator dlist_begin(dlist_t* head)
{
	assert(head);
	
	return head->head/*dlist_next(head->head)*/;
}

/***********************************************************/
dl_iterator dlist_end(dlist_t* head)
{
	dlist_t *temp = head;
	
	return temp->tail;
}

/***********************************************************/
dl_iterator dlist_next(dl_iterator iter)
{
	return iter->next;
}

/***********************************************************/
dl_iterator dlist_prev(dl_iterator iter)
{
	return iter->prev;
}

/***********************************************************/
void dlist_push_front (dlist_t* head, dl_data data)
{
	assert(head);
	dlist_insert_after(/*dlist_prev*/(dlist_begin(head)), data);
	return;
	
}

/***********************************************************/
void dlist_push_back (dlist_t* head, dl_data data)
{
	assert(head);
	
	dlist_insert_after(head->tail->prev, data);
	
	return;
		
}

/***********************************************************/
void dlist_pop_front(dlist_t* head)
{
	assert(head);
	
	dlist_remove(dlist_next(dlist_begin(head)));
	
	return;
}

/***********************************************************/
void dlist_pop_back(dlist_t* head)
{
	assert(head);
	
	dlist_remove(dlist_prev(dlist_end(head)));
	
	return;
}

/***********************************************************/
dl_iterator dlist_insert_after(dl_iterator iter, dl_data data)
{
	assert(iter);
	
	dl_iterator new_node = iter_create(data);
	
	iter->next->prev = new_node;
	new_node->next = iter->next;
	iter->next = new_node;
	new_node->prev = iter;
	/*new_node->data = data;*/
		
	return new_node;
}
/***********************************************************/
void dlist_remove(dl_iterator iter)
{
	
	if((iter->next==NULL) || (iter->prev==NULL))
	{
		return;
	}
	
	else
	{
		iter->next->prev = iter->prev;
		iter->prev->next = iter->next;
		free(iter);
	}
}

/***********************************************************/
size_t dlist_size(dlist_t *head)
{
	return dlist_foreach(dlist_next(dlist_begin(head)),dlist_end(head), useless_func, 0);
}
/***********************************************************/
int dlist_is_empty(dlist_t *head)
{
	
	if((dlist_begin(head)->next)==dlist_end(head))
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
}

/***********************************************************/
int dlist_foreach(dl_iterator from,
		  dl_iterator to,   
		  int (*func)(dl_data, void *),
		  void *param)
{
/*assert(from);
assert(to);

	for( ;dlist_next(from) < to; dlist_next(from) )
	{
		
		assert(dlist_prev(from));
		memset(dlist_prev(from), 0, sizeof(dl_node_t)); 
		free(dlist_prev(from));
	}

	return 0;*/

	int num = 0;
	
	while(from!=to)
	{
	num+=func(from->data, param);
	from = dlist_next(from);
	}

	return num;
}

/***********************************************************/
dl_iterator dlist_find(dl_iterator from,
		       dl_iterator to,
		       int (*cmp_func)(dl_data, void *),
		       void *param)
{
	while(from!=to)
	{

		if(cmp_func(from->data, param))
		{
			return from;
		}

		from = dlist_next(from);
	}

	return to;
}

/***********************************************************/
int useless(dl_data data, void* num)
{
	return 1;
}

