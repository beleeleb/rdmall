#ifndef __DLIST_H__
#define __DLIST_H__
#include <stdlib.h>

typedef struct dl_node dl_node_t; 

typedef struct dlist dlist_t;

typedef dl_node_t* dl_iterator ;

typedef void* dl_data;

/*	Creates a list.
	Parameters:N/A. 
	Returns: Pointer to a new dlist .*/
dlist_t* dlist_create(); 

/*	Destroys a given list .
	Parameters:
 	 head: Head of list to be destroyed. 
	Returns: N/A */
void dlist_destroy(dlist_t *head);


/*	Return first node in list.
	Parameters:
 	 head: Pointer to the list
	Returns: Pointer to head of list(can also return NULL, if needed).*/
dl_iterator dlist_begin(dlist_t *head); 
	
/*	Return last node in list.
	Parameters:
 	 head: Head of list . 
	Returns: Pointer to last element in list(can also return NULL, if needed).*/
dl_iterator dlist_end(dlist_t *head);

/*	Checks the next node in list.
	Parameters: 
 	 iter: Pointer to checked element. 
	Returns: Pointer to next element (can also return NULL, if needed). */
dl_iterator dlist_next(dl_iterator iter);


/*	Checks the previous node in list.
	Parameters: 
 	 iter: Pointer to checked element. 
	Returns: Pointer to previous element (can also return NULL, if needed). */
dl_iterator dlist_prev(dl_iterator iter);

/*	Returns the node's data
	Parameters: 
 	 iter: Pointer to checked element. 
	Returns: Node data */
dl_data dlist_get_data(dl_iterator iter);


/*	Creates a new node before the current head and initializes it with given data.
	Parameters: 
	 head: Head of list into which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: N/A. */
void dlist_push_front (dlist_t *head , dl_data data);


/*	Creates a new node at the end of the list and initializes it with given data.
	Parameters: 
	 head: Head of list to be removed.
	Returns: N/A. */
void dlist_push_back (dlist_t *head , dl_data data);


/*	Removes current head from list.
	Parameters: 
	 head: Head of list to be removed.
	Returns: Data of removed (old) head. */
void dlist_pop_front(dlist_t *head);


/*	Removes current tail from list.
	Parameters: 
	 head: Head of list to be removed.
	Returns: Data of removed (old) tail. */
void dlist_pop_back(dlist_t *head); 


/*	Creates and inserts a new node after given node and initializes it with given 
	data.
	Parameters: 
	 iter: Node after which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: Pointer to new value. */	
dl_iterator dlist_insert_after(dl_iterator  iter,dl_data data);


/*	Removes specific node from list.
	Parameters: 
	 iter: Node to be removed.
	Returns: data of element removed. */ 
void dlist_remove(dl_iterator iter);

/*	Checks the number of elements in list.
	Parameters: 
 	 head: Head of checked list. 
	Returns: Number of elements. */
size_t dlist_size(dlist_t *head); 


/*	Checks the number of elements in list.
	Parameters: 
 	 head: Head of checked list. 
	Returns: SUCCESS/FAIL value. */
int dlist_is_empty(dlist_t *head); 

/* foreach "from" to "to" (not including "to") */
int dlist_foreach(dl_iterator from,
		  dl_iterator to,   
		  int (*func)(dl_data, void *),
		  void *param);
		 /* runs until (not including) "to", or
				  until func returns a non-zero value */

/*searches "from" to "to" (not including "to") */
dl_iterator dlist_find(dl_iterator from,
		       dl_iterator to,
		       int (*cmp_func)(dl_data, void *),
		       void *param);


#endif /* __DLIST_H__ */
