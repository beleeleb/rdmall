#ifndef __HASH_TABLE_TYPES_H__
#define  __HASH_TABLE_TYPES_H__

#include "cdlist_types.h"

typedef void* hash_key;
typedef int (*cmp_fn_ptr)(hash_key key1 , hash_key key2);
typedef size_t (*hash_fn_ptr)(hash_key key);
typedef void* hash_data;
typedef struct hash_table hash_table_t;
typedef struct hash_element hash_element_t;

#endif /*__HASH_TABLE_TYPES_H__*/
