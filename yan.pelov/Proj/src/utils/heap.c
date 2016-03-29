#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "heap.h"

extern int compy(void* num1, void* num2);

struct heap_element
{
	heap_data    data;
	struct heap_element* parent;
	struct heap_element*  right;
	struct heap_element*  left;

};

struct heap
{
	heap_element_t* root;
	heap_cmp_func   cmp_func;
	size_t          heap_size;
};

enum RESULT {SUCCESS = 0, FAIL = 1};

heap_t* heap_create(heap_cmp_func cmp_func )
{
	assert(cmp_func);
    heap_t* new_heap = NULL;
    new_heap = (heap_t*)malloc(sizeof(heap_t));
    assert(new_heap);
    memset(new_heap, 0, sizeof(heap_t));
    
    new_heap->root = NULL;
	new_heap->heap_size = 0;
    new_heap->cmp_func = cmp_func;
    
    return new_heap;
}

void heap_destroy(heap_t** heap )
{
	return;
}

int print_all_heap(heap_element_t* elem)
{
	if(elem != NULL)
	{

		print_all_heap(elem->left);
		print_all_heap(elem->right);
		printf("elem data %ld\n", (long)elem->data);		 
	}

	return 0;
}

void print_heap_tree(heap_t* heap)
{
	heap_element_t* temp = heap->root;
	print_all_heap(temp);
}


size_t heap_size( heap_t* heap)
{
	return heap->heap_size;
}


int heap_is_empty( heap_t* heap)
{
	assert(heap);
    return (heap->root == NULL);
}

static heap_element_t* make_elem(heap_data data)
{
	heap_element_t* new_elem = NULL;
    new_elem = (heap_element_t*)malloc(sizeof(heap_element_t));
    assert(new_elem);
    memset(new_elem, 0, sizeof(heap_element_t));
    new_elem->data = data;
    new_elem->parent = NULL;
    new_elem->left = NULL;
    new_elem->right = NULL;
    
    return new_elem;
}

static heap_element_t* go_next_left(heap_element_t* elem)
{
	if(elem->left == NULL)
	{
		return elem;
	}	

	else
	{
		elem = go_next_left(elem->left);
	}
}

static heap_element_t* go_next_right(heap_element_t* elem)
{
	if(elem->right == NULL)
	{
		return elem;
	}	

	else
	{
		elem = go_next_right(elem->right);
	}
}


static int heapify(heap_t* heap, heap_element_t* elem)
{
	if((elem->parent==NULL) || heap->cmp_func(elem->parent->data, elem->data)>=0 )
	{
		return 0;
	}

	else
	{
		heap_data temp_data = NULL;
		temp_data = elem->parent->data;
		elem->parent->data = elem->data;
		elem->data = temp_data;

		heapify(heap, elem->parent);
	}
}



static heap_element_t* leftest(heap_t* heap, heap_element_t* elem, size_t size)
{

	if(size < 2)
	{
		return heap->root;
	}

	elem = leftest(heap, elem, size/2);

	if(size % 2 == 0)
	{
		elem = elem->left;
	}

	else
	{
		elem = elem->right;
	}	

	return elem;
}


int heap_insert( heap_t* heap,  heap_data data)
{
	heap_element_t* new_elem = make_elem(data);

	if(heap_is_empty(heap))
	{
		heap->root = new_elem;
		heap->heap_size += 1;
		new_elem->parent = NULL;
		return SUCCESS;
	}
	
	else
	{
		if(heap->heap_size == 1)
		{
			heap_element_t* temp = NULL;
			temp = go_next_left(heap->root);
			temp->left = new_elem;	
			new_elem->parent = temp;
			heap->heap_size += 1;
			heapify(heap, new_elem);
			return SUCCESS;
		}	
	

	
		else
		{ 
			heap_element_t* temp = NULL;

			temp = heap->root;

			int num = heap->heap_size;

			temp = leftest(heap , heap->root, (heap->heap_size + 1)/2);

			if(temp->left==NULL)
			{
					temp->left = new_elem;
					new_elem->parent = temp;
			}

			else
			{
					temp->right = new_elem;;
					new_elem->parent = temp;
			}
		
			heap->heap_size += 1;
		}
	
		heapify(heap, new_elem);
	}

}

heap_data heap_peek( heap_t* heap )
{
	if(heap == NULL || heap->root == NULL)
	{
		return NULL;
	}

	else 
	{
		return heap->root->data;
	}
}

static heap_element_t* down_heapify(heap_t* heap, heap_element_t* elem)
{
/*	heap_element_t* temp = heap->root;

	heap_data temp_data = NULL;

	if(elem->left == NULL && elem->right == NULL)
	{
		return elem;
	}

	if(elem->left == NULL && elem->right != NULL)
	{
		if(heap->cmp_func(elem->left->data, temp->data) < 0)
		{
			
			temp_data = elem->left->data;
			elem->left->data = temp->data;
			temp->data = temp_data;
			elem = down_heapify(heap, elem->left);
			elem = down_heapify(heap, elem->right);

		}
	}
	if(heap->cmp_func(elem->left->data, elem->right->data) >= 0)
	{
		if(heap->cmp_func(elem->left->data, temp->data) < 0)
		{
			
			temp_data = elem->left->data;
			elem->left->data = temp->data;
			temp->data = temp_data;
			elem = down_heapify(heap, elem->left);
			elem = down_heapify(heap, elem->right);

		}
	}

	else
	{
		if(heap->cmp_func(elem->right->data, temp->data) < 0)
		{
			
			temp_data = elem->right->data;
			elem->right->data = temp->data;
			temp->data = temp_data;
			elem = down_heapify(heap, elem->left);
			elem = down_heapify(heap, elem->right);

		}

	}

	
}
	if((elem->left==NULL) || heap->cmp_func(elem->parent->data, elem->data) < 0 )
	{
		return elem;
	}

	else
	{
		heap_data temp_data = NULL;
		temp_data = elem->parent->data;
		elem->parent->data = elem->data;
		elem->data = temp_data;

		heapify(heap, elem->parent);
	}*/
}


int heap_pop(heap_t* heap)
{
	heap_element_t* elem = NULL;
	elem = down_heapify(heap, heap->root);
	printf("%ld", elem->data);
	return 0;
}

static heap_traverse(heap_element_t* elem, heap_data* data, size_t size)
{
	static int i = 0;
	if(elem != NULL)
	{
		heap_traverse(elem->left, data, size);
		heap_traverse(elem->right, data, size);
		*(data+i) = elem->data;
		i++;		 
	}

	return 0;
}

heap_data* heap_to_array( heap_t* heap )
{
	void **array = (void*)malloc(sizeof(size_t) * heap->heap_size);
	heap_traverse(heap->root, array, heap->heap_size);
	int i = 0;
	for(i = 0; i <  heap->heap_size; i++)
	{
			printf("%d ", *(array+i));
	}
}

heap_t* array_to_heap( heap_data* data_array , size_t array_size)
{

	heap_t* new_heap = heap_create(&compy);

	int i = 0;

	for(i =0 ; i < array_size; ++i)
	{
		heap_insert(new_heap, (*(data_array+i)));
	}

	return new_heap;
}

/*heap_element_t**/
static int find_elem(heap_element_t* elem, heap_t* heap, heap_data data, heap_element_t** temp)
{
	if(elem != NULL)
	{
        if(heap->cmp_func(elem->data, data) == 0)
		{
			*temp = elem;
            return 0;
		}
        
    }
	
    if(elem == NULL)
    {
        return 1;
    }
    
    find_elem(elem->left, heap, data, temp);
    find_elem(elem->right, heap, data, temp);
}

heap_data heap_find( heap_t* heap, heap_data data)
{
	heap_element_t* temp = NULL;
    find_elem(heap->root, heap, data, &temp);
    
	if(temp != NULL) return temp->data;
    
    else return NULL;

}

void free_my_elem(heap_element_t* elem)
{
	assert(elem);
	memset(elem, 0, sizeof(heap_element_t));
	free(elem);
	elem = NULL;
    return;
}


int heap_remove( heap_t* heap, heap_data data)
{
	heap_element_t* temp = NULL;

	heap_element_t* mytemp = NULL;

	mytemp = heap->root;

	heap_data temp_data = NULL;

	find_elem(heap->root, heap, data, &temp);
	
	if(temp == NULL)
	{
		return 1; /* not found*/
	}	
	
	else
	{
		mytemp = leftest(heap , heap->root, (heap->heap_size + 1)/2);	

		printf("fff%ld %ld\n", data, mytemp->left->data);

		if(mytemp->left!=NULL)
		{				
			if(heap->cmp_func(data, mytemp->left->data) == 0)
			{

					free_my_elem(mytemp->left);
					mytemp->left = NULL;
			}
				
			else
			{	
				temp->data = mytemp->left->data;
				free_my_elem(mytemp->left);
				mytemp->left = NULL;

				if(temp->left == NULL && temp->right == NULL) return 0;
				
				if(temp->left!=NULL && temp->right == NULL)
				{
					if(heap->cmp_func(temp->left->data, temp->data)<0)
					{
						temp_data = temp->data;
						temp->data = temp->left->data;	
						temp->left->data = temp_data; 
					}
					
					else return 0;
				}

				if(temp->left==NULL && temp->right != NULL)
				{
					if(heap->cmp_func(temp->right->data, temp->data)<0)
					{
						temp_data = temp->data;
						temp->data = temp->right->data;	
						temp->right->data = temp_data; 
					}
					
					else return 0;

				}

				if(temp->left!=NULL && temp->right != NULL)
				{
					if(heap->cmp_func(temp->right->data, temp->left->data) > 0)
					{
						if(heap->cmp_func(temp->right->data, temp->data)<0)
						{
							temp_data = temp->data;
							temp->data = temp->right->data;	
							temp->right->data = temp_data; 
						}
					
						else return 0;
					}

					else
					{
						if(heap->cmp_func(temp->left->data, temp->data)<0)
						{
							temp_data = temp->data;
							temp->data = temp->left->data;	
							temp->left->data = temp_data; 
						}
					
						else return 0;

					}
				}
			}
		}

		else
		{				
			if(heap->cmp_func(data, mytemp->right->data) == 0)
			{

					free_my_elem(mytemp->right);
					mytemp->right = NULL;
			}
				
			else
			{	
				temp->data = mytemp->right->data;
				free_my_elem(mytemp->right);
				mytemp->right = NULL;
				
				if(temp->left == NULL && temp->right == NULL) return 0;
				
				if(temp->left!=NULL && temp->right == NULL)
				{
					if(heap->cmp_func(temp->left->data, temp->data)<0)
					{
						temp_data = temp->data;
						temp->data = temp->left->data;	
						temp->left->data = temp_data; 
					}
					
					else return 0;
				}

				if(temp->left==NULL && temp->right != NULL)
				{
					if(heap->cmp_func(temp->right->data, temp->data)<0)
					{
						temp_data = temp->data;
						temp->data = temp->right->data;	
						temp->right->data = temp_data; 
					}
					
					else return 0;

				}

				if(temp->left!=NULL && temp->right != NULL)
				{
					if(heap->cmp_func(temp->right->data, temp->left->data) > 0)
					{
						if(heap->cmp_func(temp->right->data, temp->data)<0)
						{
							temp_data = temp->data;
							temp->data = temp->right->data;	
							temp->right->data = temp_data; 
						}
					
						else return 0;
					}

					else
					{
						if(heap->cmp_func(temp->left->data, temp->data)<0)
						{
							temp_data = temp->data;
							temp->data = temp->left->data;	
							temp->left->data = temp_data; 
						}
					
						else return 0;

					}
				}

			
			}
		}
	
	}

	return 0;
}
/*----------------------------------------------------------------------------*/
/* recursive print heap */

void recursive_heap_print(heap_element_t* curr, size_t level)
{
    size_t lvl = level;
 
    if (curr->right) recursive_heap_print(curr->right,level+1);
  
    if (curr->parent && curr->parent->left==curr)
    {
        lvl = level-1;
        while (--lvl) printf("    ");
        printf("  \\  \n");
        lvl = level;
        while (--lvl) printf("    ");
        printf("%ld\n",(long)curr->data);
    }

    if(!curr->parent)
    {
        lvl = level;
        while (--lvl) printf("    ");
        printf("%ld\n",(long)curr->data);
    }
  

    if (curr->parent && curr->parent->right==curr)
    {
        lvl = level;
        while (--lvl) printf("    ");
        printf("%ld\n",(long)curr->data);
        lvl = level-1;
        while (--lvl) printf("    ");
        printf("  /  \n");
    }
  
    if (curr->left) recursive_heap_print(curr->left,level+1);
}

/*----------------------------------------------------------------------------*/

void print_heap(heap_t* heap)
{
    if (!heap && !heap->root) return;
    
    printf ("\nMy Heap:\n");
    printf ("---------\n");
    recursive_heap_print(heap->root , 1);
    printf ("\n\n");
}


