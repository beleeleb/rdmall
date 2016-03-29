#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "hash_table.h"
#include "cdlist.h"

struct hash_table
{
	cdl_node_t** array;
	size_t size;
	hash_fn_ptr hash_func;
	cmp_fn_ptr cmp_func;
};

struct hash_element
{
	hash_key key;
	hash_data data;	
};

hash_table_t* hash_create(size_t size, cmp_fn_ptr cmp_func, hash_fn_ptr hash_func)
{
	hash_table_t* my_table = NULL;
	my_table = (hash_table_t*)malloc(sizeof(hash_table_t));
	assert(my_table);
	memset(my_table, 0, sizeof(hash_table_t));
	
	my_table->size = size;

	my_table->array = (cdl_node_t**)malloc(sizeof(cdl_node_t*) * size);
	assert(my_table->array);
	memset(my_table->array, 0, sizeof(cdl_node_t*) * size);
	
	my_table->hash_func = hash_func;
	my_table->cmp_func = cmp_func;

	return my_table;
}


static int func(cdl_data data, void * param)
{
	hash_element_t *hash_elem = NULL;
	hash_elem = data; 

	if(data!=NULL);
	{
		memset(hash_elem, 0, sizeof(hash_element_t));
		free(hash_elem);
		hash_elem = NULL;
	}
	return 1;
}

void hash_destroy(hash_table_t* table)
{ 
	int i = 0;

	for(i = 0; i < table->size; ++i) 
	{
		cdlist_foreach(cdlist_begin(table->array[i]), /* we were asked to write this way "*(table->array +i)"*/
		      cdlist_end(table->array[i]),   
		  &func,
		  (void*)0); 

		table->array[i] = cdlist_destroy(table->array[i]);
 
	}

	memset(table->array, 0, sizeof(cdl_node_t*) * table->size);
	free(table->array);
	table->array = NULL;

	memset(table, 0, sizeof(hash_table_t));
	free(table);
	table = NULL;
	
	return;
}

size_t hash_size(hash_table_t* table) 
{
	assert(table);
	size_t count = 0;
	int i;
	
	for(i = 0; i < table->size; ++i) 
	{
		count += cdlist_size(table->array[i]); 
	}

	return count;
}

int hash_insert(hash_table_t* table, hash_key key, hash_data data)
{
	size_t index = 0;
	index = (table->hash_func(key)) % (table->size);	

	hash_element_t *elem = NULL;
	
	elem = (hash_element_t*)malloc(sizeof(hash_element_t));
	assert(elem);
	memset(elem, 0, sizeof(hash_element_t));

	elem->key = key;
	elem->data = data;

	table->array[index] = cdlist_insert_after(table->array[index], elem);

	return 0;
}

void hash_print(hash_table_t* table) 
{

	assert(table);
	int i, j;
	cdl_node_t *elem = NULL;
	hash_element_t *hash_elem = NULL;

	for(i = 0; i < table->size; i++)
	{
		elem = table->array[i]; /*  try to get used to: *(table->array +i)*/

		for(j = 0; j < cdlist_size(table->array[i]); ++j)
		{
			hash_elem = cdlist_get_data(elem);
			printf("array[%d][%d] --- data: %ld\n", i,j,(size_t)(hash_elem->data));
			elem = cdlist_next(elem);
		}
	}

}

static int cmp(cdl_data data, void * param)
{
	hash_element_t *hash_elem = NULL;
	
	hash_elem = data;
	
	return ((long)(hash_elem->key) == (long)param);
}

int hash_remove(hash_table_t* table, hash_key key) 
{
	assert(table);
	size_t index = 0;
	cdl_node_t* new_cdl_node = NULL;
	hash_element_t* hash_elem = NULL;

	index = (table->hash_func(key))%(table->size);

	new_cdl_node = cdlist_find(cdlist_begin(table->array[index]),
					cdlist_end(table->array[index]), &cmp, key);
			
	hash_elem = cdlist_get_data(new_cdl_node);

	if(hash_elem->key != key)
	{	
		return 1;
	}

	memset(hash_elem, 0, sizeof(hash_element_t));
	free(hash_elem);
	hash_elem = NULL;
	
	table->array[index] = cdlist_remove(new_cdl_node);
	
	return 0;
}

hash_data hash_get_data(hash_table_t* table, hash_key key)
{
	assert(table);
	size_t index = 0;
	cdl_node_t *elem = NULL;
	hash_element_t *hash_elem = NULL;
	index = table->hash_func(key) % (table->size); 

	elem = cdlist_find(cdlist_begin(table->array[index]),
		      cdlist_end(table->array[index]),&cmp, key);

	hash_elem = cdlist_get_data(elem);

	if(hash_elem->key != key)
	{	
		return NULL;
	}

	return hash_elem->data;
}

