#ifndef __DICTIONARY_HASH__
#define __DICTIONARY_HASH__

#include "dict_hash.h"
#include "dict_hash_types.h"

dict_hash_t* init_dictionary(int* fd);

void destroy_dictionary(int fd,dict_hash_t* hash);

int spell_check (dict_hash_t* hash,char* word);


#endif /* __DICTIONARY_HASH__*/
