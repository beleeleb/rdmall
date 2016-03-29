#ifndef __DLIST_SAFE_H__
#define __DLIST_SAFE_H__

#include "dlist.h"

typedef struct safe_dlist safe_dlist_t;
typedef struct safe_iter safe_iter_t;

/* Initialize mutex (and initialize sdlist_version to 0) and struct data.
 *  Creates a list. */
/* parameters : void
 * return: success: safe_dlist_t address.
 * 		fail: NULL.
 */
safe_dlist_t* sdlist_create(void);

/*	Destroys a given list.
Parameters:
 	sdlist: address of safe_dlist to be destroyed.
Returns: N/A */
void sdlist_destroy(safe_dlist_t *sdlist);


/*	Return first node in list.
  ---	update version of safe_iter and return
Parameters:
 	iter: safe_dlist iterator
Returns: Pointer to head of list(can also return NULL, if needed).*/
safe_iter_t* sdlist_begin(safe_iter_t* iter);

/*	Return last node in list.
Parameters:
 	head: Head of list .
Returns: Pointer to last element in list(can also return NULL, if needed).*/
safe_iter_t* sdlist_end(safe_iter_t* iter);

/*	Checks the next node in list.
Parameters:
 	iter: Pointer to checked element.
Returns: Pointer to next element (can also return NULL, if needed). */
safe_iter_t* sdlist_next(safe_iter_t * iter);


/*	Checks the previous node in list.
Parameters:
 	iter: Pointer to checked element.
Returns: Pointer to previous element (can also return NULL, if needed). */
safe_iter_t* sdlist_prev(safe_iter_t * iter);

/*	Returns the node's data
Parameters:
 	iter: Pointer to checked element.
Returns: Node data */
dl_data sdlist_get_data(safe_iter_t* iter);


/*	Creates a new node before the current head and initializes it with given data.
Parameters:
head: Head of list into which insertion is performed.
data: Data of new node to be inserted.
Returns: N/A. */
void sdlist_push_front(safe_dlist_t* sdlist , dl_data data);


/*	Creates a new node at the end of the list and initializes it with given data.
Parameters:
head: Head of list to be removed.
Returns: N/A. */
void sdlist_push_back(safe_dlist_t* sdlist , dl_data data);


/*	Removes current head from list.
Parameters:
head: Head of list to be removed.
Returns: Data of removed (old) head. */
void sdlist_pop_front(safe_dlist_t *sdlist);


/*	Removes current tail from list.
Parameters:
head: Head of list to be removed.
Returns: Data of removed (old) tail. */
void sdlist_pop_back(safe_dlist_t *sdlist);


/*	Creates and inserts a new node after given node and initializes it with given
data.
Parameters:
iter: Node after which insertion is performed.
data: Data of new node to be inserted.
Returns: Pointer to new value. */
void sdlist_insert_after(safe_iter_t *iter, dl_data data);


/*	Removes specific node from list.
Parameters:
iter: Node to be removed.
Returns: data of element removed. */
void sdlist_remove(safe_iter_t *iter);

/*	Checks the number of elements in list.
Parameters:
 	head: Head of checked list.
Returns: Number of elements. */
size_t sdlist_size(safe_dlist_t *sdlist);


safe_iter_t* sdlist_create_iter(safe_dlist_t *sdlist);

/* use this function after every version update */
void sdlist_destroy_iter(safe_iter_t *iter);


/*	Checks the number of elements in list.
Parameters:
 	head: Head of checked list.
Returns: SUCCESS/FAIL value. */
int sdlist_is_empty(safe_dlist_t *sdlist);


/*searches "from" to "to" (not including "to") */
/* usage: int cmp_func(dl_data node_data, void *param); */
safe_iter_t* sdlist_find(safe_iter_t* from,
      safe_iter_t* to,
      int (*cmp_func)(dl_data, void *),
      void *param);

/* foreach "from" to "to" (not including "to") */
int sdlist_foreach(unsigned short num_of_threads , safe_iter_t* from,
 safe_iter_t* to,
 int (*func)(dl_data, void *),
 void *param);
/* runs until (not including) "to", or
 until func returns a non-zero value */

#endif /* __DLIST_SAFE_H__ */
