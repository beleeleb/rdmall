#ifndef __CDLIST_H__
#define __CDLIST_H__

#include <stdlib.h>
#include "cdlist_types.h"

/*typedef struct cdl_node cdl_node_t;

typedef cdl_node_t* cdl_iterator;

typedef void* cdl_data;*/

cdl_iterator cdlist_create_list(); 

cdl_iterator cdlist_destroy(cdl_iterator);

cdl_iterator cdlist_begin(cdl_iterator); 

cdl_iterator cdlist_end(cdl_iterator);

cdl_iterator cdlist_next(cdl_iterator);

cdl_iterator cdlist_prev(cdl_iterator);

cdl_data cdlist_get_data(cdl_iterator);

cdl_iterator cdlist_push_front(cdl_iterator , cdl_data);

cdl_iterator cdlist_push_back(cdl_iterator , cdl_data);

cdl_iterator cdlist_pop_front(cdl_iterator);

cdl_iterator cdlist_pop_back(cdl_iterator); 

cdl_iterator cdlist_insert_after(cdl_iterator,cdl_data);

cdl_iterator cdlist_remove(cdl_iterator iter);

size_t cdlist_size(cdl_iterator); 

int cdlist_is_empty(cdl_iterator); 

int cdlist_foreach(cdl_iterator from,
		  cdl_iterator to,   
		  int (*func)(cdl_data, void *),
		  void *param); 

cdl_iterator cdlist_find(cdl_iterator from,
		       cdl_iterator to,
		       int (*cmp_func)(cdl_data, void *),
		       void *param);

#endif /* __CDLIST_H__ */
