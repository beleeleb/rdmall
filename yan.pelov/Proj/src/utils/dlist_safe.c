#include <assert.h>
#include <pthread.h>
#include "dlist_safe.h"
#include <string.h>

struct safe_dlist
{
	dlist_t *dlist;
	size_t sdlist_version;
	pthread_mutex_t sdlist_mutex;
};

struct safe_iter
{
	dl_iterator iter;
	struct safe_dlist* sdlist;
	size_t iter_version;
};

safe_dlist_t* sdlist_create(void)
{
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	safe_dlist_t * list = NULL;
	dlist_t * ptr = dlist_create();
	list = (safe_dlist_t *)malloc(sizeof(safe_dlist_t));
	memset(list, 0, sizeof(safe_dlist_t));
	list->dlist = ptr;
	list->sdlist_version = 0;
	list->sdlist_mutex = mutex;
	return list;
}

void sdlist_destroy(safe_dlist_t *sdlist)
{
	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	dlist_destroy(sdlist->dlist);
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
	pthread_mutex_destroy(&(sdlist->sdlist_mutex));
	memset(sdlist, 0, sizeof(safe_dlist_t));
	free(sdlist);
	sdlist = NULL;
}

safe_iter_t* sdlist_create_iter(safe_dlist_t *sdlist)
{
	safe_iter_t* ptr = NULL;
	ptr = (safe_iter_t*)malloc(sizeof(safe_iter_t));
	memset(ptr, 0, sizeof(safe_iter_t));
	ptr->sdlist = sdlist;
	ptr->iter = NULL;
	ptr->iter_version = 0;
	return ptr;
}

void sdlist_destroy_iter(safe_iter_t *iter)
{
	memset(iter, 0, sizeof(safe_iter_t));
	free(iter);
	iter = NULL;
}

safe_iter_t* sdlist_begin(safe_iter_t* iter)
{
	/* lock */
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	iter->iter = dlist_begin(iter->sdlist->dlist);
	iter->iter_version = iter->sdlist->sdlist_version;

	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
	return iter;
}

safe_iter_t* sdlist_end(safe_iter_t* iter)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	iter->iter = dlist_end(iter->sdlist->dlist);
	iter->iter_version = iter->sdlist->sdlist_version;
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
	return iter;
}

safe_iter_t* sdlist_next(safe_iter_t * iter)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	iter->iter = dlist_next(iter->iter);
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
	return iter;
}

safe_iter_t* sdlist_prev(safe_iter_t * iter)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	iter->iter = dlist_prev(iter->iter);
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
	return iter;
}

dl_data sdlist_get_data(safe_iter_t* iter)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	dl_data data = dlist_get_data(iter->iter);
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
	return data;
}

void sdlist_insert_after(safe_iter_t *iter, dl_data data)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	iter->iter = dlist_insert_after(iter->iter, (dl_data)data);
	iter->sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
}

void sdlist_remove(safe_iter_t *iter)
{
	pthread_mutex_lock(&(iter->sdlist->sdlist_mutex));
	dlist_remove(iter->iter);
	iter->sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(iter->sdlist->sdlist_mutex));
}

void sdlist_push_front(safe_dlist_t* sdlist , dl_data data)
{
	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	dlist_push_front(sdlist->dlist, (dl_data)data);
	sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
}

void sdlist_push_back(safe_dlist_t* sdlist , dl_data data)
{

	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	dlist_push_back(sdlist->dlist, (dl_data)data);
	sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
}

void sdlist_pop_front(safe_dlist_t *sdlist)
{

	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	dlist_pop_front(sdlist->dlist);
	sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
}

void sdlist_pop_back(safe_dlist_t *sdlist)
{

	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	dlist_pop_back(sdlist->dlist);
	sdlist->sdlist_version += 1;
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
}



size_t sdlist_size(safe_dlist_t *sdlist)
{
	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	size_t size = dlist_size(sdlist->dlist);
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
	return size;
}

int sdlist_is_empty(safe_dlist_t *sdlist)
{
	pthread_mutex_lock(&(sdlist->sdlist_mutex));
	int res = dlist_is_empty(sdlist->dlist);
	pthread_mutex_unlock(&(sdlist->sdlist_mutex));
	return res;

}

safe_iter_t* sdlist_find(safe_iter_t* from,
  safe_iter_t* to,
  int (*cmp_func)(dl_data, void *),
  void *param)
{
	pthread_mutex_lock(&(from->sdlist->sdlist_mutex));
	safe_iter_t* ptr = sdlist_create_iter(from->sdlist);
	ptr->iter = dlist_find(from, to, cmp_func, param);
	pthread_mutex_unlock(&(from->sdlist->sdlist_mutex));

	if(ptr->iter == NULL)
	{
		sdlist_destroy_iter(ptr);
		return NULL;
	}

	else return ptr;
}
/*

int sdlist_foreach(unsigned short num_of_threads , safe_iter_t* from,
safe_iter_t* to,
int (*func)(dl_data, void *),
void *param)
{

}

*/
extern void print_me(safe_dlist_t *sdlist)
{
	dlist_print(sdlist->dlist);
}




