#include <stdio.h>
#include "bin_tree.h"

extern void print_tree(tree_t* tree);
extern void print_iter(tree_iterator iter);

int compy(void* num1, void* num2)
{
	if(num1 < num2) return -1;
	if(num1 > num2) return 1;
	return 0;
}

int search(tree_data data, void* num)
{
	if(data < num) return -1;
	if(data > num) return 1;
	return 0;

}

int main(int argc, char **argv, char **epvm)
{
	tree_t *new_tree = NULL;
	function new_f = &compy;
	cmp_func new_fu = &search;
	tree_iterator temp = NULL;

	new_tree = tree_create(new_f);
	tree_insert(new_tree, (void*)100);
	tree_insert(new_tree, (void*)15);
	tree_insert(new_tree, (void*)90);

	tree_insert(new_tree, (void*)5);
	tree_insert(new_tree, (void*)65);
	tree_insert(new_tree, (void*)45);

	tree_insert(new_tree, (void*)3);
	tree_insert(new_tree, (void*)1);

	tree_insert(new_tree, (void*)2);

	tree_insert(new_tree, (void*)19);
	tree_insert(new_tree, (void*)19);
	tree_insert(new_tree, (void*)10);
	print_tree(new_tree);

	temp = tree_find(tree_begin(new_tree),tree_next(tree_end(new_tree)), new_fu, (void*)5);
	
	print_iter(temp);
	return 0;
}
