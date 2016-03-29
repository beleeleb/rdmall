#ifndef __HEAP_H__
#define  __HEAP_H__
#include "heap_types.h"

/*	This Funcion creates a new heap_t and initialize it with the given parameters.
	Parameters:
	 heap_size: the max number of elements the heap can contain. 
	 cmp_func:  A compare function, by which the heap is defined.
	 			( cmp_func return 0 if "==", n>0 if ">" and n<0 if "<" ) 
	Returns: A pointer to the new heap or NULL if fail.                                      */
heap_t* heap_create( heap_cmp_func cmp_func );


/*	This Funcion destroy a given heap and set its pointer to NULL.
	Parameters:
	 heap: The address of the pointer to the heap to destroy.  
	Returns:  <void>  */
void heap_destroy( heap_t** heap );


/*	This Funcion return the number of elements in a given heap.
	Parameters:
	 heap: A pointer to the heap.    
	Returns:   Number of elements. */
size_t heap_size( heap_t* heap);


/*	This Funcion destroy a given heap.
	Parameters:
	 heap: A pointer to the heap.   
	Returns: 1 if empty, 0 if not */
int heap_is_empty( heap_t* heap);

/*	This Funcion inserts a given data to the heap.
	Parameters:
	 heap: A pointer to the heap into which insertion is performed. 
	 data: The data to insert.
	Returns:
	 0 if insetrion was successful. 
	 1 if memory allocation failed.
	 2 if key already exist.
	 3 if other failure accured                                      */
int heap_insert( heap_t* heap,  heap_data data);


/*	This Funcion return data from the top/first element in the heap.
	Parameters:
	 heap: A pointer to the heap. 
	Returns: data from first element in heap, NULL if not found */
heap_data heap_peek( heap_t* heap );


/*	This Funcion removes the top/first element in the heap.
	Parameters:
	 heap: A pointer to the heap.  
	Returns: 0 if success or, 1 if heap empty. */
int heap_pop( heap_t* heap );


/*	This Funcion return an array with all the elements in the heap.
	The function Does not 
	Parameters:
	 heap: A pointer to the heap.  
	Returns: An array with all the elements */
heap_data* heap_to_array( heap_t* heap );


/*	This Funcion turn an array with all the elements in the heap.
	Parameters:
	 data_array: array with data;  
	 size: the data_array size
	Returns: A heap with all the elements */
heap_t* array_to_heap( heap_data* data_array , size_t array_size);


/*	This Funcion return the data of the element with a given param
	Parameters:
	 heap: A pointer to the heap to search in. 
	 param: a parameter by which to find the currect data
	 data: The data to insert.
	Returns: The data of the element , NULL if not found (what if the data IS NULL??) */
heap_data heap_find( heap_t* heap, heap_data data);
/*heap_data heap_find( heap_t* heap, void* param_to_find ,
								 int(*heap_find_func)(heap_data* data, void* param));*/

/*	This Funcion removes an element from the heap
	Parameters:
	 heap: A pointer to the heap
	 data: The data to remove.
	Returns: 0 if success */
int heap_remove( heap_t* heap, heap_data data);







#endif /*  __HEAP_H__ */
