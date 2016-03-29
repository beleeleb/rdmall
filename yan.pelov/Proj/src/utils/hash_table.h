#ifndef __HASH_TABLE_H__
#define  __HASH_TABLE_H__
#include "hash_table_types.h"

/*	Creates a new table.
	Parameters: 
 	 size: size of table.
 	 hash_func: pointer to hash function.
 	 cmp_func: pointer to compare function.
	Returns: new table. 				*/
hash_table_t* hash_create(size_t size, cmp_fn_ptr cmp_func, hash_fn_ptr hash_func);


/*	destroys a given table.
	Parameters: 
 	 table: table to destroy. 
	Returns: N/A. */
void hash_destroy(hash_table_t* table);


/*	measures the table.
	Parameters: 
 	 table: table to be measures. 
	Returns: number of hash_table elements. */
size_t hash_size(hash_table_t* table);


/*	insert data to hash table
	Parameters: 
 	 table: table to insert into
 	 key: key that the function use to insert the data (unique key).
 	 data: data to be insert
	Returns: SUCCESS/FAIL. */
int hash_insert(hash_table_t* table, hash_key key, hash_data data);


/*	removes a specific data by key.
	Parameters: 
 	 table: table to remove from.
 	 key: key that the function use to remove the data.
	Returns: SUCCESS/FAIL. */
int hash_remove(hash_table_t* table, hash_key key);


/*	gets data from table.
	Parameters: 
 	 table: table to get the data from.
 	 key: key that the function use to get the data.
	Returns: the data. */
hash_data hash_get_data(hash_table_t* table, hash_key key);



#endif	/*__HASH_TABLE_H__*/	
