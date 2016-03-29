#include <stdio.h>
#include "dlist.h"

typedef int (*func)(dl_data, void *);
int (*cmp_func)(dl_data, void *);

/*************************function declarations******************/
extern void dlist_print(dlist_t *head);
extern dl_iterator dlist_head(dlist_t* head);
int find_val(dl_data data, void* num);
extern int count(dl_data data, void* num);

/*************************main function**************************/
int main (int argc, char** argv, char** evmp)
{
	dlist_t* new_list = NULL;
	dl_iterator new_tmp = NULL;
	dl_iterator from = NULL;
	dl_iterator to = NULL;
	dl_iterator res = NULL;
	
	func find_func =&find_val;
	
	new_list = dlist_create();
	/*
	new_tmp = dlist_head(new_list);
	
	dlist_insert_after(new_tmp, (dl_data)50);
	dlist_push_front(new_list, (dl_data)100);
	dlist_push_back(new_list, (dl_data)200);
	
	from = dlist_begin(new_list);
	to = dlist_end(new_list);
	
	dlist_print(new_list);
	
	res = dlist_find(from, to,find_func, (void*) 50);
	
	dlist_remove(res);
	dlist_destroy(new_list);*/

	return 0;
}

int find_val(dl_data data, void* num)
{
	return (data == num);
}
