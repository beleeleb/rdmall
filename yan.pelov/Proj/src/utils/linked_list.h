/*  header file for linked_list.c */

#ifndef __LINKED_LIST_H__
#define  __LINKED_LIST_H__

typedef struct node node_t;
typedef void* p_data;
typedef int (*fn_ptr)(node_t* node, void* param);

/*	Checks if list is empty.
	Parameters: 
 	 root: Head of checked list. 
	Returns: TRUE/FALSE value. */
int is_empty_list(node_t* root);

/*	Checks the number of elements in list.
	Parameters: 
 	 root: Head of checked list. 
	Returns: Number of elements. */
int n_elements_list(node_t* root);


/*	Checks the next node in list.
	Parameters: 
 	 node_ptr: Pointer to checked element. 
	Returns: Pointer to next element (can also return NULL, if needed). */
node_t* next_node_list(node_t* node_ptr);


/*	Destroys given list.
	Parameters:
 	 root: Head of list to be destroyed. 
	Returns: SUCCESS/FAIL value. */
int destroy_list(node_t** root);


/*	Creates a new node before the current head and initializes it with given data.
	Parameters: 
	 root: Head of list onto which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: SUCCESS/FAIL value. */
int push_front_list(node_t** root, p_data data);


/*	Creates a new node after the current tail and initializes it with given data.
	Parameters: 
	 root: Head of list onto which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: SUCCESS/FAIL value. */
int push_back_list(node_t** root, p_data data);


/*	Removes current head from list.
	Parameters: 
	 root: Head of list to be removed.
	Returns: Data of removed (old) head. */
p_data pop_front_list(node_t** root);


/*	Removes current tail from list.
	Parameters: 
	 root: Head of list to be removed.
	Returns: Data of removed (old) tail. */
p_data pop_back_list(node_t** root);


/*	Creates and inserts a new node after given node and initializes it with given 		data.
	Parameters: 
	 ptr_node: Node after which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: SUCCESS/FAIL value. */
int insert_after_list(node_t** ptr_node, p_data data);


/*	Removes specific node from list.
	Parameters: 
	 ptr_node: Node to be removed.
	 root: Head of list.  
	Returns: data of element removed. */
p_data remove_node_list(node_t** root, node_t* ptr_node);


/*	flips direction of pointers .
	Parameters: 
	 root: Head of list.  
	Returns: SUCCESS/FAIL value. */
int flip_list(node_t** root);


/*	Checks the list for loops.
	Parameters: 
	 root: Head of list.  
	Returns: TRUE/FALSE value. */
int contains_loop_list(node_t* root);


/*	Opens existing loops.
	Parameters: 
	 root: Head of list.  
	Returns: SUCCESS/FAIL value. */
int open_loop_list(node_t* root);


/*	Finds given parameter in given range.
	Parameters: 
	 from: Search start node (including).
	 to: Search end node (not including).
	 funct_ptr: Pointer to search function (performs comparsion).
	 param_for_fn: Parameter to be searched for.
	Returns: Found data. */
node_t* find_list(node_t* from,node_t* to, fn_ptr funct_ptr, void* param_for_fn);


/*	Executes given function on each elements in given range.
	Parameters: 
	 from: Execution start node (including).
	 to: Execution end node (not including).
	 funct_ptr: Pointer to executing function.
	 param_for_fn: Parameter used by executing function to perform manipulation.
	Returns: SUCCESS/FAIL value. */
int foreach_list(node_t* from,node_t* to, fn_ptr funct_ptr, void* param_for_fn);

#endif
