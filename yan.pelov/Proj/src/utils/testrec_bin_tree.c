#include <stdio.h>
#include "rec_bin_tree.h"

extern void print_tree_node(tree_node_t* node);
extern void rec_print_tree(tree_t* tree);
extern void free_my_node(tree_node_t* node);
extern void rec_local_balance(tree_t* tree, tree_node_t* new_node);


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

int addfive(tree_data data, void * num)
{
	return 1;
}

int main(int argc, char **argv, char **epvm)
{
	tree_t *new_tree = NULL;
	tree_node_t* temp_node = NULL;
    function new_f = &compy;	
	cmp_func find_f = &search;

	func foreach_f = &addfive;

	new_tree = rec_tree_create(new_f);
    
    printf("*****is tree empty?***** = %d\n", rec_tree_is_empty(new_tree));

	rec_tree_insert(new_tree, (void*)6);
	rec_tree_insert(new_tree, (void*)5);
	rec_tree_insert(new_tree, (void*)1);
	rec_tree_insert(new_tree, (void*)2);
	rec_tree_insert(new_tree, (void*)3);
	/*rec_tree_insert(new_tree, (void*)1);
	rec_tree_insert(new_tree, (void*)2);
	rec_tree_insert(new_tree, (void*)3);*/


	/*rec_local_balance(new_tree, rec_tree_prev(rec_tree_end(new_tree)));

	*/

	/*new_tree = rec_balance(new_tree);*/
	/*print_tree_node(rec_get_root(rec_tree_begin(new_tree)));
	print_tree_node(rec_get_root(rec_tree_begin(new_tree)));*/

	
	rec_print_tree(new_tree);
	
	printf("\ntree size: %ld\n", rec_tree_size(new_tree));
	rec_tree_destroy(new_tree);

	/*print_tree_node(temp_node);

	print_tree_node(temp_node);

	rec_print_tree(new_tree);

	rec_tree_foreach(rec_tree_begin(new_tree), rec_tree_next(rec_tree_end(new_tree)), foreach_f, (void*)5);

	rec_print_tree(new_tree);

	temp_node = rec_tree_find(rec_tree_begin(new_tree), rec_tree_next(rec_tree_end(new_tree)), find_f, (void*)120);

	printf("size of tree: %ld\n--------------------------------\n", rec_tree_size(new_tree));*/
		
	/*temp_node = rec_get_root(rec_tree_begin(new_tree));*/

	/*print_tree_node(temp_node);*/

	/*temp_node = rec_tree_remove(new_tree, temp_node);

	temp_node = rec_get_root(rec_tree_begin(new_tree));

	print_tree_node(temp_node);*/

	/*print_tree_node(rec_tree_begin(new_tree));*/

	/*temp_node = rec_get_root(rec_tree_begin(new_tree));*/

	/*print_tree_node(temp_node);*/

	/*free_my_node(temp_node);

	temp_node = rec_get_root(rec_tree_begin(new_tree));

	print_tree_node(temp_node);*/
	/*rec_print_tree(new_tree);*/

	/*print_tree_node(temp_node);*/

	/*temp_node = rec_tree_remove(new_tree, rec_tree_next(temp_node));

	rec_print_tree(new_tree);*/

	/*temp_node = rec_tree_begin(new_tree);

	

	

	temp_node = rec_tree_remove(new_tree, temp_node);

	*/

	/*temp_node = rec_tree_remove(new_tree,  temp_node);

	*/


	/*rec_tree_destroy(new_tree);*/

	/**/


	
    /*
                                   
    
    tree_iterator temp = NULL;
    cmp_func new_fu = &search;


	print_tree(new_tree);

	temp = tree_find(tree_begin(new_tree),tree_next(tree_end(new_tree)), new_fu, (void*)5);
	
	prffint_iter(temp);*/
	return 0;
}
