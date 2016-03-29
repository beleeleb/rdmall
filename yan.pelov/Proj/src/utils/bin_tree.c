#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "bin_tree.h"

struct tree_node
{
	tree_data data;
	struct tree_node *parent;
	struct tree_node *left;	
	struct tree_node *right;
};

struct tree
{
	struct tree_node *root;
	function       compare;
}; 


tree_iterator get_root(tree_iterator iter)
{
	if (iter == NULL)
	{
		return NULL;
	}
	while(iter->parent != NULL)
	{
		iter = iter->parent;
	}
    
    return iter;
}

int append(tree_data data, void* num)
{
	return 0;
}

void print_iter(tree_iterator iter)
{
	printf("\niter: %ld\n", (long)tree_get_data(iter));
}

void print_tree(tree_t* tree)
{
	tree_iterator temp;

	temp = tree_begin(tree);

	do
	{
		print_iter(temp);
		temp = tree_next(temp);
	} while(temp != NULL);

	printf("-----------------------------"); 
	temp = tree_end(tree);
	
	do
	{
		print_iter(temp);
		temp = tree_prev(temp);
	} while(temp != NULL);

}


tree_t* tree_create(function compare)
{
	assert(compare);
	tree_t* new_tree = NULL;
	new_tree = (tree_t*)malloc(sizeof(tree_t));
	assert(new_tree);
	memset(new_tree, 0, sizeof(tree_t));

	new_tree->root = NULL;
	new_tree->compare = compare;

	return new_tree;
}

void tree_destroy(tree_t* tree)
{
	assert(tree);
	return;
}

tree_iterator tree_begin(tree_t* tree)
{
	assert(tree);
	tree_iterator temp = tree->root;

	while(temp->left != NULL)
	{
		temp = temp->left;
	}

	return temp;
}

tree_iterator tree_end(tree_t* tree)
{
	assert(tree);
	tree_iterator temp = tree->root;

	while(temp->right != NULL)
	{
		temp = temp->right;
	}

	return temp;
}


tree_iterator tree_next(tree_iterator iter)
{
	tree_iterator temp = NULL;
	if(iter == NULL)
	{
		return NULL;
	}

	if(iter->right != NULL)
	{
		temp = iter->right;
	
		while(temp->left != NULL)
		{
			temp = temp->left;
		}

		return temp;
	}

	temp = iter;

	while( (temp->parent != NULL) && (temp != temp->parent->left) )
	{
		temp = temp->parent;
	}
	return temp->parent;
}


tree_iterator tree_prev(tree_iterator iter)
{
	tree_iterator temp = NULL;
	if(iter == NULL)
	{
		return NULL;
	}

	if(iter->left != NULL)
	{
		
		temp = iter->left;
	
		while(temp->right != NULL)
		{
			temp = temp->right;
		}

		return temp;
	}

	temp = iter;

	while ( temp->parent!=NULL && temp != (temp->parent)->right )
	{
			temp = temp->parent;
	}
	return temp->parent;                                
}

static tree_iterator make_node(tree_data data)
{
	tree_node_t *new_node = NULL;
	new_node = (tree_node_t*)malloc(sizeof(tree_node_t));
	assert(new_node);
	memset(new_node, 0, sizeof(tree_node_t));
	new_node->data = data;
	new_node->parent = NULL;
	new_node->left = NULL;
	new_node->right = NULL;

	return new_node;
}

int tree_insert(tree_t* tree, tree_data data)
{
	assert(tree);
	tree_node_t *new_node = make_node(data);
	tree_iterator temp_iter = NULL;
	int result = 3;

	if(tree_is_empty(tree))
	{
		tree->root = new_node;
        new_node->parent = NULL;
		return 0;
	}

	temp_iter = tree->root;

	while(1)
	{
		result = tree->compare(tree_get_data(temp_iter), data);

		if(result == 0)
		{
			printf("Can't insert - same num in tree\n");
			free(new_node);
			return 0;
		}
		if(result < 0 && temp_iter->right == NULL)
		{
            new_node->parent = temp_iter;
			temp_iter->right = new_node;
            printf("\nnew_node->parent: %ld\n", (long)tree_get_data(new_node->parent));
            printf("\ntemp_iter->right: %ld\n", (long)tree_get_data(temp_iter->right));
			return 0;
		}

		if(result < 0 && temp_iter->right != NULL)
		{
			temp_iter = temp_iter->right;
		}

		if(result > 0 && temp_iter->left == NULL)
		{
            new_node->parent = temp_iter;
            temp_iter->left = new_node;
			printf("\nnew_node->parent: %ld\n", (long)tree_get_data(new_node->parent));
            printf("\ntemp_iter->left: %ld\n", (long)tree_get_data(temp_iter->left));			
			return 0;
		}

		 if(result > 0 && temp_iter->left != NULL)
		{
			temp_iter = temp_iter->left;
		}
	}
	
	return 0;

}

static void free_node(tree_iterator iter)
{
	assert(iter);
	memset(iter, 0, sizeof(tree_node_t));
	free(iter);
	iter = NULL;
}

tree_iterator tree_remove(tree_t* tree, tree_iterator iter)
{
	assert(tree);

	if(iter->parent == NULL && iter->left == NULL && iter->right== NULL)
	{
		free_node(iter);
	}

	

    return 0;
}

tree_data tree_get_data(tree_iterator iter)
{
	assert(iter);
	return iter->data;
}


size_t tree_size(tree_t* tree)
{
	assert(tree);
	func new_fu = &append;
	return tree_foreach(tree_begin(tree), tree_next(tree_end(tree)), new_fu, (void*)1);
}

int tree_is_empty(tree_t* tree)
{
	assert(tree);
	return (tree->root == NULL);
}


int tree_foreach(tree_iterator from,
		  tree_iterator to,   
		  int (*func)(tree_data, void *), 
		  void *param)
{
	int counter = 0;

	while (from != to)
	{
		if ( func(tree_get_data(from), param) != 0 )
		{
			return counter;
		}

		++counter;
		from = tree_next(from);
	}
	return counter;
}

tree_iterator tree_find(tree_iterator from,
		       tree_iterator to,
		       int (*cmp_func)(tree_data, void *),
		       void *param)
{

	while(from != to)
	{
		if(cmp_func(tree_get_data(from), param) == 0)
		{
			return from;
		}

		from = tree_next(from);
	}

	return to;
}

tree_t* balance(tree_t* tree)
{
	assert(tree);
	return 0;
}  
