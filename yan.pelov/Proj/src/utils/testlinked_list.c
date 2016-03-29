#include <stdio.h>
#include "linked_list.h"

extern void makeloop(node_t *root);
extern void print_nodes(node_t* root);
extern void func_node(node_t* node_ptr, void* data);

int new_func(node_t* node, void* num);

int main (int argc, char** argv, char** evm)
{
	node_t *root = NULL;

	insert_after_list(&root, (void *)100);
	
	push_front_list(&root, (void *)200);

	push_back_list(&root, (void *)300);





	print_nodes(root);
	makeloop(root);
	open_loop_list(root);
	
	print_nodes(root);

	fn_ptr new_f = &new_func;
	
	find_list(root,root, new_f, (void*)5);
	
	return 0;
}

int new_func(node_t* node, void* num)
{
	func_node(node, num);
	return 0;
}



