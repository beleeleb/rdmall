/*******************************************************************************
 DESCRIPTION:  This program implements a A Binary Search Tree
                                                                              
 DATE: 20 oct 2014                                                         
                                                                              
 NAME: Alex Salomon
 
 COMPILTAION LINE:  gcc -ansi -Wall bin_tree.c test_bin_tree.c -lm                  
*******************************************************************************/

#ifndef __BIN_TREE_H__
#define  __BIN_TREE_H__

typedef int(*function)(void*, void*); /* compare function */

typedef struct tree_node tree_node_t; 

typedef tree_node_t* tree_iterator ;

typedef void* tree_data;

typedef int (*func)(tree_data, void *);

typedef int (*cmp_func)(tree_data, void *);

typedef struct tree tree_t;

/* do we need get data function?? */


/*	find the root of the tree .
	Parameters: 
	 iter: a node in the tree
	Returns: the root of the tree*/
tree_iterator get_root(tree_iterator iter);


/*	Creates a node and initializes it with given data.
	Parameters: N/A . 
	Returns: new tree.*/
tree_t* tree_create(function compare);	

/*	Destroys a given tree .
	Parameters:
 	 root: root of tree to be destroyed. 
	Returns: N/A */
void tree_destroy(tree_t* tree); 


/*	Return first node in tree.
	Parameters:
 	 root: Pointer to the root of tree.
	Returns: Pointer to begining of tree ("smallest" element in tree)*/
tree_iterator tree_begin(tree_t* tree);  

	
/*	Return last node in tree.
	Parameters:
 	 root: Pointer to the root of tree.
	Returns: Pointer to last element in tree (can also return NULL, if needed).*/
tree_iterator tree_end(tree_t* tree); 


/*	Checks the next node in tree.
	Parameters: 
 	 iter: Pointer to checked element. 
	Returns: Pointer to next element (can also return NULL, if needed). */
tree_iterator tree_next(tree_iterator iter);


/*	Checks the previous node in tree.
	Parameters: 
 	 iter: Pointer to checked element. 
	Returns: Pointer to previous element (can also return NULL, if needed). */
tree_iterator tree_prev(tree_iterator iter); 


/*	Creates and inserts a new node into the tree
	Parameters: 
	 tree: the tree into which insertion is performed.
	 data: Data of new node to be inserted.
	Returns: success/failure. */	
int tree_insert(tree_t* tree, tree_data data);


/*	Removes specific node from tree.
	Parameters: 
	 iter: Node to be removed.
	 tree: the treeo on which removal is performed.
	Returns: The removed node. */ 
tree_iterator tree_remove(tree_t* tree, tree_iterator iter);

/*	Checks the data of the element.
	Parameters: 
 	 iter: Pointer to  element. 
	Returns: data of element  */
tree_data tree_get_data(tree_iterator iter); 

/*	Checks the number of elements in tree.
	Parameters: 
 	 tree: the tree to measure. 
	Returns: Number of elements. */
size_t tree_size(tree_t* tree); 


/*	Checks if the tree empty.
	Parameters: 
 	 tree: the tree to check. 
	Returns: TRUE/FALSE value. */
int tree_is_empty(tree_t* tree); 


/*  foreach "from" to "to" (not including "to") runs until func returns a non-zero value.
	Parameters: 
 	 from: the node to start from.
 	 to: the node to stop at.
 	 func: the pointer to function.
 	 param: the parameter the function is using.
	Returns: number of times the func function returned success . */
int tree_foreach(tree_iterator from,
		  tree_iterator to,   
		  int (*func)(tree_data, void *), 
		  void *param); 


/*  searches "from" to "to" (not including "to").
	Parameters: 
 	 from: the node to start from.
 	 to: the node to stop at.
 	 cmp_func: the pointer to function.
 	 param: the parameter the function is using.
	Returns: iterator containing the found data or "to" if not found . */
tree_iterator tree_find(tree_iterator from,
		       tree_iterator to,
		       int (*cmp_func)(tree_data, void *),
		       void *param);


/*	balances a given tree.
	Parameters: 
 	 tree: tree to balance. 
	Returns: balanced tree. */    
tree_t* balance(tree_t* tree);	       


#endif /*	__BIN_TREE_H__	*/

