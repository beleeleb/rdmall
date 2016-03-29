#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "dict_hash.h"
#include "dict_hash_types.h"
#include "rec_bin_tree.h"
#define MYSIZE 10

int dict_hash_cmp(dict_hash_key key1 , dict_hash_key key2);
size_t dict_hash_func(dict_hash_key key);

int main(int argc, char **argv, char **epvm)
{
	dict_hash_t* new_table = NULL;	
	new_table = dict_hash_create(MYSIZE, &dict_hash_cmp, &dict_hash_func);

	dict_hash_key key1 = (void*)123;
	dict_hash_data data1 = (char*)"apple"; 
	dict_hash_key key2 = (void*)45;
	dict_hash_data data2 = (char*)"water"; 
	dict_hash_insert(new_table, key1, data1);	
	dict_hash_insert(new_table, key2, data2);	

	dict_hash_data temp_data = NULL;
	temp_data = dict_hash_get_data(new_table, (void*)123);
	size_t n_elements = 0;
	n_elements = dict_hash_size(new_table);
	printf("temp_data: %s\tn_elements: %ld\n", temp_data, n_elements);

	dict_hash_remove(new_table, (void*)45);

	n_elements = dict_hash_size(new_table);

	printf("n_elements: %ld\n", n_elements);

	dict_hash_destroy(new_table);
	
	return 0;
}

int dict_hash_cmp(dict_hash_key key1 , dict_hash_key key2)
{
	if(key1 < key2) return -1;
	if(key1 > key2) return 1;
	return 0;
}

size_t dict_hash_func(dict_hash_key key)
{
	size_t result = 0;
	result = ((size_t)key % MYSIZE);
	return result;
}

