#include <stdio.h>
#include "reclist.h"


extern void print_nodes1(node_t* root);

extern void* get_data1(node_t* node_ptr);

int main (int argc, char** argv, char** evm)
{
	node_t *root = NULL;	
	
	insert_after_list1(&root, (void *)100);

	push_back_list1(&root, (void *)200);

	push_back_list1(&root, (void *)300);

	push_back_list1(&root, (void *)400);

	push_back_list1(&root, (void *)500);
	
	print_nodes1(root);

	printf("\n");

	flip_list2(&root);

	print_nodes1(root);

	return 0;
}



