#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "rec_bin_tree_2.h"

struct tree_node
{
	tree_data data;
	struct tree_node *left;	
	struct tree_node *right;
};

struct tree
{
	struct tree_node *root;
};

void free_my_node(tree_node_t* node)
{
	assert(node);
	memset(node, 0, sizeof(tree_node_t));
	free(node);
	node = NULL;
    return;
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

tree_t* rec_tree_create(void)
{
    tree_t* new_tree = NULL;
    new_tree = (tree_t*)malloc(sizeof(tree_t));
    assert(new_tree);
    memset(new_tree, 0, sizeof(tree_t));
    new_tree->root = NULL;
    return new_tree;
}

static tree_node_t* make_node(tree_data data)
{
    tree_node_t* new_node = NULL;
    new_node = (tree_node_t*)malloc(sizeof(tree_node_t));
    assert(new_node);
    memset(new_node, 0, sizeof(tree_node_t));
    new_node->data = data;
    /*new_node->parent = NULL;*/
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}
/*
tree_node_t* rec_tree(tree_t* tree, tree_node_t* temp_node, int result, tree_node_t *new_node)
{	
	result = tree->compare(rec_tree_get_data(temp_node), rec_tree_get_data(new_node));
        
    if(result == 0)
    {
        printf("Can't insert - equal number in tree\n");
        free_my_node(new_node);
        return 0;
    }

    if(result < 0 && temp_node->right == NULL)
    {
        new_node->parent = temp_node;
        temp_node->right = new_node;
       
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
        	
        return 0;
    }
    
    if(result > 0 && temp_node->left != NULL)
    {
        temp_node = rec_tree(tree, temp_node->left,result,new_node);
    }
}
*/
int rec_tree_insert(tree_t* tree, tree_data data)
{

    assert(tree);

	if(tree = NULL)
	{
		tree = rec_tree_create();
		tree->root->data = data;
	}


    /*
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
    }*/
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

/*static size_t size_traverse(tree_node_t* node)
{
	static size_t counter = 0;

	if(node != NULL)
	{
		inorder_traverse(node->left);
		inorder_traverse(node->right);
		counter++;
	}

	return counter;
}*/


void inorder_traverse(tree_node_t* node)
{
	if(node != NULL)
	{
		inorder_traverse(node->left);
		printf("%ld\n", (long)node->data);
		inorder_traverse(node->right);
	}
}


void rec_tree_destroy(tree_t* tree)
{	
	assert(tree);
	free(tree);
	tree = NULL;
	return;
}



