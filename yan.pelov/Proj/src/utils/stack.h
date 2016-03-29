#ifndef __STACK_H__
#define  __STACK_H__

	struct stack_t;
	typedef struct stack_t stack;
	 
	stack * stack_create(size_t size);
	  
	int stack_destroy(stack *s);

	int stack_is_full(const stack *const s);

	int stack_is_empty(const stack *const s);

	size_t stack_capacity(const stack *const s);

	void* stack_peek(const stack * const s);

	void* stack_pop(stack * const s);

	int stack_push(stack * const s, void* data);

	size_t stack_n_elements(const stack *const s);

	void print_stack(stack *s);

#endif
