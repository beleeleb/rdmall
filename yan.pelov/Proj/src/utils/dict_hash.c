#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "dict_hash.h"
#include "dict_hash_types.h"
#include "rec_bin_tree.h"

extern void* print_tree_node2(tree_node_t* node);

struct dict_hash
{
   void** hash_array;
   dict_hash_f hash_f_ptr; 
   dict_cmp_f cmp_f_ptr;
   size_t size;
};

struct dict_hash_element
{
	dict_hash_key key;
	dict_hash_data data;	
};

dict_hash_t* dict_hash_create(size_t size, dict_cmp_f cmp_f, dict_hash_f hash_f)
{
	dict_hash_t* my_table = NULL;
	my_table = (dict_hash_t*)malloc(sizeof(dict_hash_t));
	assert(my_table);
	memset(my_table, 0, sizeof(dict_hash_t));
	
	my_table->size = size;
	my_table->hash_array = (void **)malloc(sizeof(tree_t*) * size);
	assert(my_table->hash_array);
	memset(my_table->hash_array, 0, sizeof(tree_t*) * size);

	int i = 0;

	for(i = 0; i < size; ++i)
	{
		my_table->hash_array[i] = rec_tree_create(cmp_f);
	}
	
	my_table->hash_f_ptr = hash_f;
	my_table->cmp_f_ptr = cmp_f;
	
	return my_table;
}

size_t dict_hash_size(dict_hash_t* table)
{
	assert(table);
	size_t count = 0;

	int i;

	for(i = 0; i < table->size; ++i) 
	{
		count += rec_tree_size(table->hash_array[i]); 
	}

	return count;
}

static int destroy_data(tree_data data1, void * data2)
{
	dict_hash_element_t* new_elem = data1;
	static int count = 0;
	

	if(new_elem->data!=NULL)
	{
		free(new_elem->data);
		new_elem->data = NULL;
	}
	memset(new_elem, 0, sizeof(dict_hash_element_t));
	free(new_elem);
	new_elem = NULL;	
} 

void dict_hash_destroy(dict_hash_t* table)
{
	int i = 0;

	tree_t* new_tree = NULL;
	tree_node_t* new_node = NULL;
	
	
	for(i = 0; i < table->size; ++i)
	{
		new_tree = table->hash_array[i];
		rec_tree_foreach(rec_tree_begin(new_tree), rec_tree_next(rec_tree_end(new_tree)), &destroy_data, (void*)0);
		rec_tree_destroy(new_tree);
		new_tree = NULL;
	}
	
	memset(table->hash_array, 0, sizeof(tree_t*) * table->size);
	free(table->hash_array);
	table->hash_array = NULL;
	
	memset(table, 0, sizeof(dict_hash_t));
	free(table);
	table = NULL;

	return;
}

static dict_hash_element_t* make_dict_element(dict_hash_key key, dict_hash_data data)
{
	dict_hash_element_t* new_elem = NULL;
	new_elem = (dict_hash_element_t*)malloc(sizeof(dict_hash_element_t));
	assert(new_elem);
	memset(new_elem, 0, sizeof(dict_hash_element_t));
	new_elem->key = key;
	new_elem->data = data;
	printf("before: %s\n", new_elem->data);
	return new_elem;
}

int dict_hash_insert(dict_hash_t* table, dict_hash_key key, dict_hash_data data)
{
	size_t index = 0;
	index = (table->hash_f_ptr(key)) % (table->size);
	dict_hash_element_t* new_elem = make_dict_element(/*key*/(void*)table->hash_f_ptr(key), data);
	rec_tree_insert(table->hash_array[index], new_elem);
	table->hash_array[index] = rec_balance(table->hash_array[index]);

	return 0;
}

void* dict_hash_get_data(dict_hash_t* table, dict_hash_key key)
{
	assert(table);

	size_t index = 0;
	tree_t* new_tree = NULL;
	tree_node_t* new_node = NULL;
	dict_hash_element_t* new_elem = NULL;

	index = table->hash_f_ptr(key) % (table->size); 

	new_tree = table->hash_array[index];
	new_node = rec_tree_begin(new_tree);
	new_elem = rec_tree_get_data(new_node);
	return new_elem->data;

}

int dict_hash_remove (dict_hash_t* table, dict_hash_key key)
{
	size_t index = 0;
	index = (table->hash_f_ptr(key)) % (table->size);
	tree_node_t* new_node = NULL;
	new_node = dict_hash_find(table, key);
	dict_hash_element_t* new_elem = NULL;

	new_elem = rec_tree_get_data(new_node);

	memset(new_elem, 0, sizeof(dict_hash_element_t));
	free(new_elem);
	new_elem = NULL;

	rec_tree_remove(table->hash_array[index], new_node);
	return 0;
}

static local_cmp(dict_hash_element_t* new_elem, dict_hash_key key)
{
	/*printf("key1 - %ld\tkey2 - %ld\n", new_elem->key, key);*/
	if((size_t)new_elem->key < (size_t)key) return -1;
	if((size_t)new_elem->key > (size_t)key) return 1;
	return 0;
}

void* dict_hash_find(dict_hash_t* table, dict_hash_key key)
{
	size_t index = 0;
	index = (table->hash_f_ptr(key)) % (table->size);
	tree_node_t* new_node = NULL;
	dict_hash_element_t* new_elem = NULL;

	new_node = rec_tree_find(rec_tree_begin(table->hash_array[index]), 
					rec_tree_next(rec_tree_end(table->hash_array[index])), &local_cmp, /*key*/table->hash_f_ptr(key));

	if(new_node!= NULL)
	{
		new_elem = rec_tree_get_data(new_node);
		if(new_elem!=NULL)
		{
			return new_elem->data;
		}	
	}

	else return NULL;	
}

void* return_key(dict_hash_element_t* new_elem)
{
	return new_elem->key;
}

void print_my_hash(dict_hash_t* table)
{
	int i = 0;
	dict_hash_element_t* new_elem = NULL;
	
	for(i = 0; i <10; ++i)
	{
		
		new_elem = print_tree_node2(rec_tree_begin(table->hash_array[i]));
	 	if(new_elem!=NULL) printf("key: %ld\tword: %s\n", new_elem->key, new_elem->data);

		new_elem = print_tree_node2(rec_tree_next(rec_tree_begin(table->hash_array[i])));
	 	if(new_elem!=NULL) printf("key: %ld\tword: %s\n", new_elem->key, new_elem->data);

		new_elem = print_tree_node2(rec_tree_next(rec_tree_next(rec_tree_begin(table->hash_array[i]))));
	 	if(new_elem!=NULL) printf("key: %ld\tword: %s\n", new_elem->key, new_elem->data);
	}
}

