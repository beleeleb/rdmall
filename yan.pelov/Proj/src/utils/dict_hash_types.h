#ifndef __DICT_HASH_TYPES__
#define __DICT_HASH_TYPES__ 

typedef void* dict_hash_key;
typedef void* dict_hash_data;
typedef int (*dict_cmp_f)(dict_hash_key, dict_hash_key);
typedef size_t(*dict_hash_f)(dict_hash_key);  
typedef struct dict_hash dict_hash_t;
typedef struct dict_hash_element dict_hash_element_t;

#endif /* __DICT_HASH_TYPES__*/


