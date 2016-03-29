#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "stack.h"
#include "utils.h"

struct stack_t
{
    void **data;
    size_t  max_size;
    size_t  top;  
};

enum ERROR 
{
    SUCCESS,   
    FAIL = -1 
};

/*-------------------------------------------------*/
stack * stack_create(size_t size)
{
	stack *new_stack = NULL;
	new_stack = (stack *)malloc(sizeof(stack));
	assert(new_stack);
	memset(new_stack, 0, sizeof(stack)); 	
	
	new_stack->max_size = size;
	new_stack->data = NULL;
	new_stack->data = (void **)malloc(sizeof(void *)*size);
	assert(new_stack->data);
	memset(new_stack->data, 0, sizeof(void *)*size);
	
	new_stack->top = 0;
	
	return new_stack;

}

/*-------------------------------------------------*/
int stack_destroy(stack *s)
{
	assert(s->data);
	memset(s->data, 0, sizeof(void *)*(s->max_size)); 
	free(s->data);
	s->data = NULL;

	if(s->data == NULL)
	{	
		assert(s);
		memset(s, 0, sizeof(stack)); 
		free(s);
		s = NULL;
	
		if(s == NULL) return SUCCESS;
		else return FAIL;
	
	} 
	else return FAIL;
}

/*-------------------------------------------------*/
int stack_is_full(const stack *const s)
{
	assert(s);
	
	return (s->top == (s->max_size));
}

/*-------------------------------------------------*/
int stack_is_empty(const stack *const s)
{	
	assert(s);
	
	return (s->top <= 0);
}

/*-------------------------------------------------*/
size_t stack_capacity(const stack *const s)
{
	assert(s);
	
	return s->max_size;
}

/*-------------------------------------------------*/
void* stack_peek(const stack * const s)
{
	assert(s);
	
	if(!stack_is_empty(s))
	{
		return s->data[s->top - 1];
	}
	
	else
	{	
		return NULL; 
	}
}

/*-------------------------------------------------*/
void* stack_pop(stack *s)
{
	void * new = NULL;
	
	if(!stack_is_empty(s))
	{
		new = s->data[s->top - 1];
		s->data[s->top - 1] = '\0';
		--(s->top);
		return new;
	}
	
	else
	{	
		return NULL;
	}		
}

/*-------------------------------------------------*/
int stack_push(stack * const s, void* data)
{
	if(!stack_is_full(s))
	{
		++(s->top);
		s->data[s->top - 1] = data;
		return SUCCESS;
	}
	
	else 
	{
		return FAIL;
	}
}

/*-------------------------------------------------*/
size_t stack_n_elements(const stack *const s)
{
	return s->top;
}

/*-------------------------------------------------*/
void print_stack(stack *s)
{
	size_t i = 0;

	for (i = 0; i < 50 ; i++)   
	{
		printf("i = %lu \t top = %lu \t stack_value = %c\n", i,
				s->top, (char *)s->data[i]);

	}

}
