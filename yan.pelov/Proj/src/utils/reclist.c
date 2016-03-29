#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "reclist.h"

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

void* get_data1(node_t* node_ptr)
{
	if(node_ptr == NULL) return NULL;

	 return node_ptr->data;
}

/***********************************************************/

extern void print_nodes1(node_t* root)
{
	node_t* temp = root; 
	
	if(!temp)
	{
		printf("\nThe list is empty\n");
	}

	do
	{
		printf("%ld\n",(long)temp->data);
		temp = temp->next;
	} while (temp!= NULL);
}

/***********************************************************/

int is_empty_list1(node_t* root)
{
	if(root == NULL)
	{
		return TRUE;
	}
	
	return FALSE;

}

/***********************************************************/

int n_elements_list1(node_t* root)
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


node_t* next_node_list1(node_t* node_ptr)
{
	return node_ptr->next;
}

/***********************************************************/

int destroy_list1(node_t** root)
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

int push_front_list1(node_t** root, p_data data)
{
	node_t* new_node = NULL;
	new_node = (node_t*)malloc(sizeof(node_t));
	memset(new_node, 0, sizeof(node_t));
	assert(new_node);
	new_node->data = data;
	
	if(*root)
	{
		new_node->next = *root;
		*root = new_node;
		return SUCCESS;
	}
	
	new_node->next = NULL;
	*root = new_node; 
	return SUCCESS;	
}
/***********************************************************/

int push_back_list1(node_t** root, p_data data)
{
	node_t* temp = *root;
	node_t* new_node =(node_t*)malloc(sizeof(node_t));
	memset(new_node, 0, sizeof(node_t));
	assert(new_node);
	new_node->data = data;

	if(is_empty_list1(temp))
	{
		new_node->next = NULL;
		*root = new_node; 
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


p_data pop_front_list1(node_t** root)
{
	node_t* new_head = (*root)->next;
	void* data = (*root)->data;
	*root = new_head;
	return data;
}
/***********************************************************/


p_data pop_back_list1(node_t** root)
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


int insert_after_list1(node_t** ptr_node, p_data data)
{
	node_t* new_node = NULL;
	new_node = (node_t*)malloc(sizeof(node_t));
	memset(new_node, 0, sizeof(node_t));
	assert(new_node);
	new_node->data = data;
	
	if(*ptr_node == NULL)
	{	
		new_node->next = NULL;
		*ptr_node = new_node; 
		return SUCCESS;		
	}

	new_node->next = (*ptr_node)->next;
	(*ptr_node)->next = new_node;
	 return SUCCESS;				
}
/***********************************************************/

p_data remove_node_list1(node_t** root, node_t* ptr_node)
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

node_t* flip_list1(node_t* root)
{
    if(root == NULL)
	{
		return NULL;
	}

	if(root->next == NULL)
	{
		return root;
	}

	node_t* temp = root;
    
    temp = flip_list1(root->next);

    root->next->next = root;
    root->next = NULL;

	return temp;
}

node_t* iter_flip(node_t* root)
{

	if(root == NULL)
	{
		return NULL;
	}

	node_t* curr = root;
	node_t* prev = NULL;
	node_t* next = NULL;

	while(curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	return prev;

}

void flip_list2(node_t** root)
{
	if((*root == NULL) || ((*root)->next==NULL)) return;

	node_t* curr = *root;
	
	*root = (*root)->next;

	flip_list2(root);

	curr->next->next = curr;
	curr->next = NULL;	
}

/*
int flip_list1(node_t** root)
{
	node_t* temp = *root;

	if(temp->next == NULL) 
	{
		return 0;
	}
	*root = temp->next;
	flip_list1(root);
	temp->next->next = temp;
	temp->next = NULL;

	return 0;
}*/
	
	/*size_t size = n_elements_list1(*root);

	
	do
	{
		
		temp = temp->next;
	
	} while (temp->next!= NULL);*/

/*	swap_me(root, temp);*/

	
	/*if(is_empty_list1(*root))
	{
		printf("\nNo can do, list is empty\n");
		return FAIL;
	}

	if(!(*root)->next)
	{
		printf("\nNo can do, there is only one element in the list\n");
		return FAIL;
	}*/

	
	/*if(!temp)
	{
		printf("\nThe list is empty\n");
	}

	do
	{
		printf("%ld\n",(long)temp->data);
		temp = temp->next;
	} while (temp!= NULL);(

	do
	{
		temp = (*root)->next;
	} while(temp->next!=NULL);

	printf("%ld", temp->data);*/

	/*if(temp->next == NULL)
	{
		swap_me(root, &temp);	
	}
	
	flip_list1(&(*root)->next);

	temp = (*root)->next;
		
	swap_me(root, &temp);

	if(temp->next == NULL) return SUCCESS;*/
		 


/*-------------------------------------------

	node_t* current = *root;
	void** adrr_arry = NULL;
	int i=0;
	int size;

	if(is_empty_list1(current))
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
}*/

