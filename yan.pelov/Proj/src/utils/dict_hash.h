#ifndef __DICT_HASH__
#define __DICT_HASH__
#include "dict_hash_types.h"

dict_hash_t* dict_hash_create(size_t size, dict_cmp_f cmp_f, dict_hash_f hash_f);

size_t dict_hash_size(dict_hash_t* table);

void dict_hash_destroy(dict_hash_t* table);

int dict_hash_insert(dict_hash_t* table, dict_hash_key key, dict_hash_data data);

dict_hash_data dict_hash_get_data(dict_hash_t* table, dict_hash_key key);

int dict_hash_remove(dict_hash_t* table, dict_hash_key key);

void* dict_hash_find(dict_hash_t* table, dict_hash_key key);

#endif /*__DICT_HASH__*/









