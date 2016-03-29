#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rec_bin_tree.h"
void inorder_traverse(tree_node_t* node);

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

void free_my_node(tree_node_t* node)
{
	assert(node);
	memset(node, 0, sizeof(tree_node_t));
	free(node);
	node = NULL;
    return;
}

tree_node_t* rec_get_root(tree_node_t* node)
{
    
    if(node == NULL)
    {
        return NULL;
    }
    
    if(node->parent == NULL) /*root found*/
    {
        return node;
    }
    
    else
    {
        node = rec_get_root(node->parent);
    }
}

void print_tree_node(tree_node_t* node)
{	
	if(node == NULL)
	{
		printf("Node is NULL\n");
		return;
	}

	printf("\nNODE: %ld\n", (long)rec_tree_get_data(node));
    return;
}

void* print_tree_node2(tree_node_t* node)
{	
	if(node == NULL)
	{
		printf("Node is NULL\n");
		return NULL;
	}

	return rec_tree_get_data(node);
}

void rec_print_tree(tree_t* tree)
{
	tree_node_t* temp = NULL;

	printf("-------------FROM TOP TO BOTTOM----------------"); 

	if(tree == NULL)
	{
		printf("Tree is empty\n");
		return;
	}
    
	temp = rec_tree_begin(tree);
	
	do
	{
		print_tree_node(temp);
		temp = rec_tree_next(temp);
	} while(temp != NULL);

	printf("-------------FROM BOTTOM TO TOP------------------");
    
	temp = rec_tree_end(tree);
	
	do
	{
		print_tree_node(temp);
		temp = rec_tree_prev(temp);
	} while(temp != NULL);
	printf("-------------------------------------------------");
}


tree_t* rec_tree_create(function compare)
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

static tree_node_t* rec_tree_begin_node(tree_node_t* node)
{
	if(node->left == NULL)
	{
		return node;
	}	

	node = rec_tree_begin_node(node->left);
}

tree_node_t* rec_tree_begin(tree_t* tree)
{
	assert(tree);
	tree_node_t* temp = NULL;

	if(tree->root == NULL)
	{
		return NULL;
	}
	
	else
	{
    	temp = rec_tree_begin_node(tree->root);
		return temp;
	}
}

tree_node_t* rec_tree_end_node(tree_node_t* node)
{
	if(node->right == NULL)
	{
		return node;
	}	

	node = rec_tree_end_node(node->right);
}

tree_node_t* rec_tree_end(tree_t* tree)
{
    assert(tree);

	if(tree->root == NULL)
	{
		return NULL;
	}

	else
	{
		tree_node_t* temp = rec_tree_end_node(tree->root);
		return temp;
	}
}

tree_node_t* rec_tree_lparent(tree_node_t* node)
{
	if((node->parent == NULL) || (node == node->parent->left))
	{
		return node->parent;
	}	
	
	else
	{
		node = rec_tree_lparent(node->parent);
	}
}	

tree_node_t* rec_tree_rparent(tree_node_t* node)
{
	if((node->parent == NULL) || (node == node->parent->right))
	{
		return node->parent;
	}	
	
	else
	{
		node = rec_tree_rparent(node->parent);
	}
}	

tree_node_t* rec_tree_next(tree_node_t* node)
{	
	if(node == NULL)
	{
		return NULL;
	}

	if(node->right != NULL)
	{
		node = node->right;
		return rec_tree_begin_node(node);
	}

	if(node->right == NULL)
	{
		node = rec_tree_lparent(node);
		return node;
	}
}

tree_node_t* rec_tree_prev(tree_node_t* node)
{
    if(node == NULL)
	{
		return NULL;
	}

	if(node->left != NULL)
	{
		node = node->left;
		return rec_tree_end_node(node);
	}

	if(node->left == NULL)
	{
		node = rec_tree_rparent(node);
		return node;
	}
}

static tree_node_t* make_node(tree_data data)
{
    tree_node_t* new_node = NULL;
    new_node = (tree_node_t*)malloc(sizeof(tree_node_t));
    assert(new_node);
    memset(new_node, 0, sizeof(tree_node_t));
    new_node->data = data;
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

tree_node_t* rec_tree(tree_t* tree, tree_node_t* temp_node, int result, tree_node_t *new_node)
{	
	result = tree->compare(rec_tree_get_data(temp_node), rec_tree_get_data(new_node));
        
    if(result == 0)
    {
        printf("Can't insert - equal number in  tree\n");
        free_my_node(new_node);
        return 0;
    }

    if(result < 0 && temp_node->right == NULL)
    {
        new_node->parent = temp_node;
        temp_node->right = new_node;
       /* printf("\nnew_node->parent: %ld\n", (long)rec_tree_get_data(new_node->parent));
        printf("\ntemp_node->right: %ld\n", (long)rec_tree_get_data(temp_node->right));*/
        return 0;
    }
    
    if(result < 0 && temp_node->right != NULL)
    {
        temp_node = rec_tree(tree ,temp_node->right, result, new_node);
    }
    
    if(result > 0 && temp_node->left == NULL)
    {
        new_node->parent = temp_node;
        temp_node->left = new_node;
        /*printf("\nnew_node->parent: %ld\n", (long)rec_tree_get_data(new_node->parent));
        printf("\ntemp_node->left: %ld\n", (long)rec_tree_get_data(temp_node->left));	*/		
        return 0;
    }
    
    if(result > 0 && temp_node->left != NULL)
    {
        temp_node = rec_tree(tree, temp_node->left,result,new_node);
    }
}

int rec_tree_insert(tree_t* tree, tree_data data)
{
    assert(tree);
    
    tree_node_t *new_node = make_node(data);

    tree_node_t* temp_node = NULL;
    
    int result = 0;
    
    if(rec_tree_is_empty(tree))
    {
        tree->root = new_node;
        new_node->parent = NULL;
        return 0;
    }
    
    else
    {
        temp_node = tree->root;
        rec_tree(tree ,temp_node, result, new_node);
        return 0;
    }
}

tree_data rec_tree_get_data(tree_node_t* node)
{
    assert(node);
    return node->data;
}

int thunk(tree_data data, void* num)
{
	return 0;
}

static size_t size_traverse(tree_node_t* node)
{
	static size_t counter = 0;

	if(node != NULL)
	{
		inorder_traverse(node->left);
		inorder_traverse(node->right);
		counter++;
	}

	return counter;
}

size_t rec_tree_size(tree_t* tree)
{
	/*return size_traverse(tree->root);*/
   assert(tree);
	func new_fu = &thunk;
	
	return (size_t)rec_tree_foreach(rec_tree_begin(tree), rec_tree_next(rec_tree_end(tree)), new_fu, (void*)0) ;
}

int rec_tree_is_empty(tree_t* tree)
{
    assert(tree);
    return (tree->root == NULL);
}


int rec_tree_foreach(tree_node_t* from,
                     tree_node_t* to,
                     int (*func)(tree_data, void *),
                     void *param)
{
	if(from == to)
	{
		return 0;
	}

    if(func(rec_tree_get_data(from), param) != 0)
    {
		return rec_tree_foreach(rec_tree_next(from), to, func, param) + 1;
	}

	else return 0;
}


tree_node_t* rec_tree_find(tree_node_t* from,
                            tree_node_t* to,
                            int (*cmp_func)(tree_data, void *),
                            void *param)
{
	assert(from && to);

	int res = 0;
	
	if(from!=to)
	{
		res =cmp_func(rec_tree_get_data(from), param);
		
		if(res!=0)
		{

		return rec_tree_find(rec_tree_next(from), to, cmp_func, param); 
		}
	
	return from;

	}

	return NULL;
	
/*  if(cmp_func(rec_tree_get_data(from), param) == 0)
	{
		return from;
	}
    
  else
  {
        return to; 
  }

    
 rec_tree_find(rec_tree_next(from), to, cmp_func, param);  */
}

void inorder_traverse(tree_node_t* node)
{
	if(node != NULL)
	{
		inorder_traverse(node->left);
		printf("%ld\n", (long)node->data);
		inorder_traverse(node->right);
	}
}

int height(tree_node_t* node)
{

   if (node == NULL)
   {
       return 0;
   }

   else
   {
       int lDepth = height(node->left);
       int rDepth = height(node->right);
 
       if (lDepth > rDepth)
	   {
			return(lDepth+1);
	   }

       else
	   {
			return(rDepth+1);
	   }

   }

}

tree_node_t* rec_tree_remove(tree_t* tree, tree_node_t* node)
{
	assert(tree);
	
	tree_data temp_data = NULL;

	if(node == NULL)
	{
		printf("Node is null\n");
		return NULL;
	}

	if(node->left!=NULL && node->right!=NULL)
	{
		temp_data = node->data;
		node = rec_tree_next(node);
		node->data = temp_data;
	}

	if(node == tree->root)
	{

		if(node->left == NULL && node->right == NULL)
		{
			tree->root = NULL;
			return node;   /*Root with no sons */
		}
	
		if(node->left == NULL && node->right != NULL)
		{
			node->right->parent = NULL;	
			tree->root = node->right;					
		}

		if(node->right == NULL && node->left != NULL)
		{
			node->left->parent = NULL;			
			tree->root = node->left;	
		}

	return node;

	}

	if(node->left == NULL && node->right != NULL)
	{
		if(node == node->parent->left)
		{
			node->parent->left = node->right;	
		}

        if(node == node->parent->right)
		{
			node->parent->right = node->right;
		}	

		node->right->parent = node->parent;	
	}

	if(node->right == NULL && node->left != NULL)
	{
		if(node == node->parent->left)
		{
			node->parent->left = node->left;	
		}

        if(node == node->parent->right)
		{
			node->parent->right = node->left;
		}	

		node->left->parent = node->parent;	
	}

	if(node->left == NULL && node->right == NULL)
	{
   		if(node == node->parent->left)
		{
			node->parent->left =  NULL;	
		}

		if(node == node->parent->right)
		{
			node->parent->right =  NULL;
		}
	}
    
    return node;
}

static void nodes_destroy(tree_t* tree, tree_node_t* from, tree_node_t* to)
{
	if(from == to)
	{
		return;
	}

	tree_node_t* temp = NULL;

	nodes_destroy(tree ,rec_tree_next(from), to);

	temp = rec_tree_remove(tree, from);

	free_my_node(temp);


}

void rec_tree_destroy(tree_t* tree)
{
	
	assert(tree);
	nodes_destroy(tree, rec_tree_begin(tree), rec_tree_next(rec_tree_end(tree)));
	free(tree);
	tree = NULL;
	
	return;
}

static void left_left_rotation(tree_t* tree, tree_node_t* new_node)
{
	if ( (!(new_node->parent->right)) && (!(new_node->parent->parent->right)) )	   /*************LEFT - LEFT ROTATION ***************/
		{																
			tree_node_t* ancestor = new_node->parent->parent->parent;
	
			if(ancestor != NULL)
			{																									
				if (new_node->parent->parent == ancestor->left)
				{
					ancestor->left = new_node->parent;
				}
				
				if (new_node->parent->parent == ancestor->right)
				{
					ancestor->right = new_node->parent;
				}
			}

			else 
			{																			
				tree->root = new_node->parent;
			}
	
			new_node->parent->right = new_node->parent->parent;
			new_node->parent->parent = ancestor;
			new_node->parent->right->parent = new_node->parent;
			new_node->parent->right->left = NULL;
		}

	return;
}

static void right_right_rotation(tree_t* tree, tree_node_t* new_node)
{
																	
		tree_node_t* ancestor = new_node->parent->parent->parent;

		if(ancestor != NULL)
		{	
			if (new_node->parent->parent == ancestor->left)
			{
				ancestor->left = new_node->parent;
			}
				
			if (new_node->parent->parent == ancestor->right)
			{
				ancestor->right = new_node->parent;
			}
		}

		else 
		{
			tree->root = new_node->parent;
		}

		new_node->parent->left = new_node->parent->parent;
		new_node->parent->parent = ancestor;
		new_node->parent->left->parent = new_node->parent;
		new_node->parent->left->right = NULL;		
	/*}*/

	return;	
}

void rec_local_balance(tree_t* tree, tree_node_t* new_node)
{																				
		if ( (!(new_node->parent->right)) && (!(new_node->parent->parent->right)) )	   /*************LEFT - LEFT LOCAL BALANCE ***************/
		{																
			left_left_rotation(tree, new_node);
		}

		if ( (!(new_node->parent->left)) && (!(new_node->parent->parent->left)) )			/*************RIGHT - RIGHT LOCAL BALANCE ***************/
		{																				
			right_right_rotation(tree, new_node);
		}
	

		if ( (!(new_node->parent->left)) &&  (!(new_node->parent->parent->right)))			/*************LEFT - RIGHT LOCAL BALANCE ***************/
		{	
			tree_data temp_data = NULL;
			temp_data = new_node->data;
			new_node->data = new_node->parent->data;
			new_node->parent->data = temp_data;

			new_node->parent->left = new_node;
			new_node->parent->right = NULL;		
		
			left_left_rotation(tree, new_node);					
		}																				

		if ( (!(new_node->parent->right) ) && (!(new_node->parent->parent->left)))			/*************RIGHT - LEFT LOCAL BALANCE ***************/
		{	
			tree_data temp_data = NULL;
			temp_data = new_node->data;
			new_node->data = new_node->parent->data;
			new_node->parent->data = temp_data;

			new_node->parent->right = new_node;
			new_node->parent->left = NULL;		
		
			right_right_rotation(tree, new_node);							
		}

	return;
}

tree_t* rec_balance_me(tree_t* tree, tree_node_t* node)
{
	if(node == NULL)
	{
		return NULL;
	}

	else
	{
		int max_l = height(node->left);
		int max_r = height(node->right);

		if(abs(max_l - max_r) > 1)
		{
			if((max_l - max_r) < 0)
			{
				node = node->right;
				max_l = height(node->left);
				max_r = height(node->right);

				if(max_l > max_r)
				{ 
					rec_local_balance(tree, node->left);

				}

				else
				{
					rec_local_balance(tree, node->right);

				}
			}

			else
			{
				node = node->left;
				max_l = height(node->left);
				max_r = height(node->right);

				if(max_l > max_r)
				{ 
				rec_local_balance(tree, node->left);

				}

				else
				{
					rec_local_balance(tree, node->right);

				}
			}
		}
		
		else
		{
			rec_balance_me(tree, node->right);
			rec_balance_me(tree, node->left);
		}
	}
}

tree_t* rec_balance(tree_t* tree)
{
	rec_balance_me(tree, tree->root);

	return tree;
	
}

