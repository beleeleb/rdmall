#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "cdlist.h"
#include "utils.h"

/***********************function declarations*******************/

extern void cdlist_print(cdl_iterator start);

typedef int (*func)(cdl_data, void *);

typedef int (*cmp_func)(cdl_data, void *);

int thunk(cdl_data data, void* num);
extern int cmp(cdl_data data, void* num);


/********************end of function declaration****************/

enum BOOLEAN
{
	FALSE = 0, TRUE = 1
};

enum RESULT
{
	SUCCESS = 0, FAIL = 1
};

struct cdl_node
{
	cdl_data *data;
	struct cdl_node *prev;
	struct cdl_node *next;
};

/***********************************************************/

static cdl_iterator iter_create(cdl_data data)
{
	cdl_iterator new_iter = NULL;
	
	new_iter = (cdl_node_t*)malloc(sizeof(cdl_node_t));
	assert(new_iter);
	memset(new_iter, 0, sizeof(cdl_node_t));
	new_iter->data = data;
	new_iter->next = NULL;
	new_iter->prev= NULL;
	return new_iter;
}



/***********************************************************/
cdl_iterator cdlist_create_list()
{
	return NULL;
}

/***********************************************************/

extern void cdlist_print(cdl_iterator start)
{

	cdl_iterator temp = start;
	
	if(cdlist_is_empty(temp))
	{
		printf("No elements in list\n");
		return;
	}
	
	do 									
	{
		printf("INSIDE:%ld\t%ld\t%ld\n", (long int)cdlist_get_data(cdlist_prev(temp)),(long int)cdlist_get_data(temp), (long int)cdlist_get_data(cdlist_next(temp)));
		temp = cdlist_next(temp);
	} while(temp != start);

	
}

/***********************************************************/

cdl_data cdlist_get_data(cdl_iterator iter)
{
	if(cdlist_is_empty(iter)) return NULL;
	assert(iter);
	return iter->data;
}

/***********************************************************/
cdl_iterator destroy_node(cdl_iterator node)	
{
	assert(node);
	memset(node, 0, sizeof(cdl_node_t));
	free(node);
	node = NULL;
	return node;
}

/***********************************************************/
cdl_iterator cdlist_destroy(cdl_iterator start)
{
	
if(start == NULL)
	{
		return NULL;
	}
	
	assert(start);
	if(start->next == start)
	{
		start = destroy_node(start);
		return start;
	}
	
	cdl_iterator temp = NULL;

	start->prev->next = NULL;
	
	while(start) 
	{
		temp = start;
		start = cdlist_next(start);
		memset(temp, 0, sizeof(cdl_node_t)); 
		free(temp);	
		temp = NULL;
	}
	
	free(start);
	start = NULL;
	return start;	
}

/***********************************************************/
cdl_iterator cdlist_begin(cdl_iterator start)
{
	return start;
}

/***********************************************************/
cdl_iterator cdlist_end(cdl_iterator start)
{
	return start;
}

/***********************************************************/
cdl_iterator cdlist_next(cdl_iterator iter)
{
	return iter->next;
}

/***********************************************************/
cdl_iterator cdlist_prev(cdl_iterator iter)
{
	return iter->prev;
}

/***********************************************************/
cdl_iterator cdlist_push_front (cdl_iterator start, cdl_data data)
{
	if(!start)
	{		
		start = cdlist_insert_after(start, data);
		return start;
	}
	
	if(start->next==start || start->prev == start)
	{
		assert(start);
		start = cdlist_insert_after(start->prev, data);
		return start;
	}

	else
	{
		assert(start);		
		start = cdlist_insert_after(start->prev, data);
		return start;
	}
}

/***********************************************************/
cdl_iterator cdlist_push_back (cdl_iterator start, cdl_data data)
{	
	if(start==NULL)
	{			
		start = cdlist_insert_after(start, data);
		return start;
	}
	
	if(start->next==start || start->prev == start)
	{
		assert(start);
		start = cdlist_insert_after(start, data);
		return start->prev;
	}
	
	else
	{
		assert(start);
		start = cdlist_insert_after(start->prev, data);
		return start->next;
	}
}

/***********************************************************/
cdl_iterator cdlist_pop_front(cdl_iterator start)
{	
	if(start == NULL)
	{
		printf("nothing to pop\n");
		return NULL;

	}	

	assert(start);
	
	if(start->next==start || start->prev == start)
	{
		start = cdlist_remove(start);
		return start;
	}
	
	else
	{
		start = cdlist_remove(cdlist_begin(start));
		return start;
	}
}

/***********************************************************/
cdl_iterator cdlist_pop_back(cdl_iterator start)
{
	if(start == NULL)
	{
		printf("nothing to pop\n");
		return NULL;

	}

	assert(start);
	

	if(start->next==start || start->prev == start)
	{
		start = cdlist_remove(start);
		return start;
	}

	else 
	{
		start = cdlist_remove(cdlist_prev(cdlist_end(start)));
		return start;	
	}
}

/***********************************************************/
cdl_iterator cdlist_insert_after(cdl_iterator iter, cdl_data data)
{
	cdl_iterator new_node = NULL;
	
	if(!iter)
	{
		new_node = iter_create(data);
		
		new_node->prev = new_node;
		new_node->next = new_node;
		
		iter = new_node;
		return new_node;
	} 
	
	assert(iter);
	
	
	new_node = iter_create(data);
		
	new_node->prev = iter;
	new_node->next = iter->next;
	
	iter->next->prev = new_node;
	iter->next = new_node;	
	
	return new_node;
}

/***********************************************************/
cdl_iterator cdlist_remove(cdl_iterator iter)
{
	assert(iter);
	
	if(iter->next==iter || iter->prev == iter)
	{
		iter = destroy_node(iter);
		return iter;
	}
	
	else
	{
		cdl_iterator temp = iter->next;

		iter->prev->next = iter->next;
		iter->next->prev = iter->prev;
		iter = destroy_node(iter);
		return temp;
	}
}

/***********************************************************/
size_t cdlist_size(cdl_iterator start)
{
	func new_f = &thunk;
	return cdlist_foreach(cdlist_begin(start),cdlist_end(start), new_f, 0);
}
/***********************************************************/
int cdlist_is_empty(cdl_iterator start)
{
	
	if(cdlist_begin(start) == NULL)
	{
		return TRUE;
	}
	
	else
	{
		return FALSE;
	}
}

/***********************************************************/
int cdlist_foreach(cdl_iterator from,
		  cdl_iterator to,   
		  int (*func)(cdl_data, void *),
		  void *param)
{
	int num = 0;
	
	if(cdlist_is_empty(from))
	{
		/*printf("List is empty\n");*/
		return num;
	}

	assert(from && to);
	
	do 									
	{
		num += func(from->data, param);
		from = cdlist_next(from);
	} while(from != to);

	return num;
}

/***********************************************************/
cdl_iterator cdlist_find(cdl_iterator from,
		      cdl_iterator to,
		       int (*cmp_func)(cdl_data, void *),
		       void *param)
{
	if(cdlist_is_empty(from))
	{
		printf("List is empty\n");
		return NULL;
	}

	do 									
	{
		if(cmp_func(from->data, param))
		{
			return from;
		}
		
		from = cdlist_next(from);
		
	} while(from != to);
	
	return to;
}

/***********************************************************/
int thunk(cdl_data data, void* num)
{
	return 1;
}

int cmp(cdl_data data, void* num)
{
	return (data==num);
}

