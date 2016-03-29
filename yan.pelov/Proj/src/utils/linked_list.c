#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"

/*int func_load();
int func_call(node_t* node_ptr, void* num);
int add_five(node_t* node_ptr, void* num);*/

enum BOOLEAN
{
	FALSE = 0, TRUE = 1
};

enum RESULT
{
	SUCCESS = 0, FAIL = 1
};

struct node 
{
	void* data;
	struct node* next;
};

/***********************************************************/

extern void func_node(node_t* node_ptr, void* data)
{
	node_ptr->data += (int)data;
}

/***********************************************************/

extern void print_nodes(node_t* root)
{
	node_t* temp = root; 
	
	if(!temp)
	{
		printf("\nlist is empty\n");
	}

	while(temp)
	{
		printf("%d\n",(int)temp->data);
		temp = temp->next;
		/*check if there is a loop*/
	}
}

/***********************************************************/

int is_empty_list(node_t* root)
{
	if(root == NULL)
	{
		return TRUE;
	}
	
	return FALSE;

}

/***********************************************************/

int n_elements_list(node_t* root)
{
	int count = 0;
	
	node_t* temp = root;
	
	while(temp)
	{
		temp = temp->next; 
		++count;	
	}
	
	return count;
}
/***********************************************************/


node_t* next_node_list(node_t* node_ptr)
{
	return node_ptr->next;
}

/***********************************************************/

int destroy_list(node_t** root)
{
	node_t* temp = NULL;

	while(*root)
	{
		temp = *root;
		*root = (*root)->next;
		memset(temp, 0, sizeof(node_t)); 
		free(temp);	
	}
		
	*root = NULL;

	return SUCCESS;
}
/***********************************************************/

int push_front_list(node_t** root, p_data data)
{
	node_t* new_node = NULL;
	new_node = (node_t*)malloc(sizeof(node_t));
	memset(new_node, 0, sizeof(node_t));
	assert(new_node);


	if(*root != NULL)
	{
		new_node->data = (*root)->data;
		(*root)->data = data;
		new_node->next = (*root)->next;
		(*root)->next = new_node;

		return SUCCESS;

	}

	new_node->data = data;

	new_node->next = NULL;
	*root = new_node; 

	return SUCCESS;	
}
/***********************************************************/

int push_back_list(node_t** root, p_data data)
{
	node_t* temp = *root;
	node_t* new_node =(node_t*)malloc(sizeof(node_t));
	memset(new_node, 0, sizeof(node_t));
	assert(new_node);
	new_node->data = data;

	if(is_empty_list(temp))
	{
		temp = new_node;
		return SUCCESS;
	}
	
	while(temp->next)
	{
		temp = temp->next;
	}
	
	temp->next = new_node;	
	return SUCCESS;
}
/***********************************************************/


p_data pop_front_list(node_t** root)
{
	node_t* new_head = (*root)->next;
	void* data = (*root)->data;
	*root = new_head;
	return data;
}
/***********************************************************/


p_data pop_back_list(node_t** root)
{
	node_t* current = NULL;
	current = *root;
	void* data = NULL;
	
	if(NULL==current)
	{
		printf("\nThe list is empty, there is nothing to pop\n");
		return data;
	}
	
	if(NULL==(current->next))
	{	
		data = current->data;
		memset(current, 0, sizeof(node_t));
		free(current);
		*root = NULL;
		return data;		
	}
	
	while(current->next->next != NULL)
	{
		current = current->next;
	}
	
	data = current->next->data;
	free(current->next);
	current->next = NULL;
	
	return data;
}
/***********************************************************/


int insert_after_list(node_t** ptr_node, p_data data)
{
	node_t* new_node = NULL;
	new_node = (node_t*)malloc(sizeof(node_t));
#ifdef DEBUG
	assert(new_node);
#endif
	memset(new_node, 0, sizeof(node_t));

	new_node->data = data;
	
	if(*ptr_node != NULL)
	{
		new_node->next = (*ptr_node)->next;
		(*ptr_node)->next = new_node;
	
		return SUCCESS;		
		
	}
	
	new_node->next = NULL;
	(*ptr_node) = new_node; 
	
	return SUCCESS;		
	
}
/***********************************************************/

p_data remove_node_list(node_t** root, node_t* ptr_node)
{
	node_t* current = *root;
	node_t* next_node = NULL;
	void* data = NULL;

	if(!ptr_node)
	{	
		printf("Error - a NULL pointer, list is empty\n");
		return data;
	}
	
	data = ptr_node->data;

	if(ptr_node->next!= NULL)
	{
		
		next_node = ptr_node->next;
	
		ptr_node->data = next_node->data;	
		ptr_node->next = next_node->next;
	
		memset(next_node, 0, sizeof(node_t));
		free(next_node);
	
	}
	
	else
	{
		
		if(current==ptr_node)
		{
			memset(ptr_node, 0, sizeof(node_t));
			free(ptr_node);	
			current = NULL;
			return data;
		}

		while(current->next!= ptr_node) 
		{
			current = current->next;
		}
		
		current->next = NULL;
		memset(ptr_node, 0, sizeof(node_t));
		free(ptr_node);	
	}
	
	return data;
	
}
/***********************************************************/


int flip_list(node_t** root)
{
	node_t* current = *root;
	void** adrr_arry = NULL;
	int i=0;
	int size;
	if(is_empty_list(current))
	{
		printf("\nNo can do, list is empty\n");
		return FAIL;
	}

	if(!current->next)
	{
		printf("\nNo can do, there is only one element in the list\n");
		return FAIL;
	}

	else
	{
		size = n_elements_list(current);
		adrr_arry = malloc(sizeof(void*) * size);

		while(current)
		{
			*(adrr_arry+i) = current->data;
			++i;
			current = current->next; 
		}

		current = *root;
		i = 0;

		while(current)
		{
			current->data = *(adrr_arry+size-1-i);
			current= current->next;
			++i;
		}
		
	}
	return SUCCESS;
}
/***********************************************************/
extern void makeloop(node_t *root)
{
	node_t* current = root;

	while(current->next)
	{
		
		printf("\n%ld", (long)current->data);
		current = current->next;
	}
	
	current->next = root;
}

/***********************************************************/


int contains_loop_list(node_t* root)
{
	node_t* current = root;

	if(is_empty_list(current))
	{
		printf("\nList is empty\n");
		return FALSE;
	}

	while(current->next!=root)
	{
		if(current->next==NULL)
		{
			return FALSE;
		}
		current = current->next;
	}
	
	return TRUE;
}
/***********************************************************/

int open_loop_list(node_t* root)
{
	node_t* current = root;

	if(contains_loop_list(root))
	{
		while(current->next!=root)
		{
			current = current->next;
		}
		
		current->next = NULL;
	}

	return SUCCESS;
}

/***********************************************************/
/*
int func_load()
{
	new_func = malloc(sizeof(int(*)(node_t*, void*)));
	memset(new_func, 0, sizeof(int(*)(node_t*, void*)));
	new_func = add_five;
	return SUCCESS;
}




int func_call(node_t* node_ptr, void* num)
{
	int tmp = 0;
	tmp = new_func(node_ptr, num);
	return tmp;
}




int add_five(node_t* node_ptr, void* num)
{
	void* tmp = node_ptr->data;
	tmp += (int)num;	
	node_ptr->data = tmp;
	return SUCCESS;
}
*/
/***********************************************************/

node_t* find_list(node_t* from,node_t* to, fn_ptr funct_ptr, void* param_for_fn)
{
	funct_ptr(from, (void*)param_for_fn);
	return 0;
}
/***********************************************************/


int foreach_list(node_t* from,node_t* to, fn_ptr funct_ptr, void* param_for_fn)
{
	return 0;
}
/***********************************************************/

