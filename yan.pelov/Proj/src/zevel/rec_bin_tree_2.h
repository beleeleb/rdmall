#ifndef __REC_BIN_TREE_2_H__
#define  __REC_BIN_TREE_2_H__

typedef int(*function)(void*, void*); 

typedef struct tree_node tree_node_t;

typedef void* tree_data;

typedef int (*func)(tree_data, void *);

typedef int (*cmp_func)(tree_data, void *);

typedef struct tree tree_t;

tree_node_t* rec_get_root(tree_node_t* node);

tree_t* rec_tree_create(void);

void rec_tree_destroy(tree_t* tree);

int rec_tree_insert(tree_t* tree, tree_data data);

tree_node_t* rec_tree_remove(tree_t* tree, tree_node_t* node);

tree_data rec_tree_get_data(tree_node_t* node);

int rec_tree_is_empty(tree_t* tree);

int rec_tree_foreach(tree_node_t* from,
		  tree_node_t* to,
		  int (*func)(tree_data, void *), 
		  void *param); 

tree_node_t* rec_tree_find(tree_node_t* from,
		       tree_node_t* to,
		       int (*cmp_func)(tree_data, void *),
		       void *param);

tree_t* rec_balance(tree_t* tree);


#endif /*	__REC_BIN_TREE_2_H__	*/

