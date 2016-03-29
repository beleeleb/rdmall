#include <stdio.h>
#include "cdlist.h"

typedef int (*func)(cdl_data, void *);

typedef int (*cmp_func)(cdl_data, void *);

extern int cmp(cdl_data data, void* num);

/*************************function declarations******************/

extern void cdlist_print(cdl_iterator start);

/*************************main function**************************/
int main (int argc, char** argv, char** evmp)
{
	cdl_iterator new_list = NULL;
	new_list = cdlist_create_list();	
	
	new_list = cdlist_push_back (new_list, (void*)100); 
	new_list = cdlist_pop_front(new_list);
	new_list = cdlist_push_back (new_list, (void*)200);
	new_list = cdlist_push_front(new_list,(void*)400);
	new_list = cdlist_push_back (new_list, (void*)300);
	new_list = cdlist_push_front(new_list, (void*)500);


	new_list = cdlist_pop_front(new_list);
	new_list = cdlist_pop_back(new_list);

	cdlist_print(new_list);

	cdlist_destroy(new_list);

	return 0;
}


