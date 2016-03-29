#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "hash_table.h"
#include "cdlist.h"
#define MYSIZE 10

int hash_cmp(hash_key key1 , hash_key key2);
size_t hash_func(hash_key key);

extern void hash_print(hash_table_t* table);

int main(int argc, char **argv, char **epvm)
{
	size_t num = 0;
	hash_table_t *new_table = NULL;
	cmp_fn_ptr new_hc = &hash_cmp;
	hash_fn_ptr new_hf = &hash_func;
	hash_data mydata = NULL;
	srand(time(NULL));

	/*hash_key key = (void*)999;
	hash_data data = (void*)100; 
	hash_key key2 = (void*)887;
	hash_data data2 = (void*)200; 
	hash_key key3 = (void*)175;
	hash_data data3 = (void*)300; 
	hash_key key4 = (void*)7676;
	hash_data data4 = (void*)400; 
	hash_key key5 = (void*)6666;
	hash_data data5 = (void*)500; 
	hash_key key6 = (void*)767;
	hash_data data6 = (void*)600; 
	hash_key key7 = (void*)444;
	hash_data data7 = (void*)320; 
	hash_key key8 = (void*)4445;
	hash_data data8 = (void*)560; */
	
	hash_key temp_key;
	hash_data temp_data;
	int i;
	hash_key temp_arr[400];
	new_table = hash_create(400, new_hc, new_hf);

	for(i = 0; i < 100; i++)
	{
		temp_key = (void *)(rand()%100);
		temp_arr[i] = (int*)temp_key;
		temp_data = (void *)i;
		hash_insert(new_table, temp_key, temp_data);		
	}

	num = hash_size(new_table);

	printf("size: %ld\n", num);

	hash_print(new_table);

	mydata = hash_get_data(new_table, (void*)1);

	printf("get data test of key %d: == %ld\n", 1 ,(long)mydata);

	for(i = 0; i < 100; i++)
	{
		temp_key = temp_arr[i];
		hash_remove(new_table, (void*)temp_key);	
	}
	
	/*new_table = hash_create(MYSIZE, new_hc, new_hf);

	hash_insert(new_table, key, data);

	hash_insert(new_table, key2, data2);

	hash_insert(new_table, key3, data3);

	hash_insert(new_table, key4, data4);

	hash_insert(new_table, key5, data5);

	hash_insert(new_table, key6, data6);

	num = hash_size(new_table);

	printf("size: %ld\n", num);

	

	hash_print(new_table);

	
	mydata = hash_get_data(new_table, key4);

	printf("get data test of key %ld: == %ld\n", (long)key4 ,(long)mydata);


	hash_remove(new_table, key4);

	mydata = hash_get_data(new_table, key4);

	printf("get data test of key %ld: == %ld\n", (long)key4 ,(long)mydata);

	hash_remove(new_table, key);

	*/

	/*

	hash_insert(new_table, key7, data7);

	hash_insert(new_table, key8, data8);

	hash_remove(new_table, key8);

	

	
	hash_print(new_table);

	num = hash_size(new_table);

	printf("size: %ld\n", num);

	*/
	printf("----------------------------------------------------\n");
	hash_print(new_table);
	num = hash_size(new_table);

	printf("size: %ld\n", num);
	hash_destroy(new_table);

	return 0;
}

int hash_cmp(hash_key key1 , hash_key key2)
{
	return 1;
}

size_t hash_func(hash_key key)
{
	size_t result = 0;
	result = ((size_t)key % MYSIZE);
	return result;
}
