#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <math.h>

#include "dictionary_hash.h"
#include "dict_hash_types.h"
#include "dict_hash.h"

extern void* return_key(dict_hash_element_t* new_elem);

int dict_hash_cmp(dict_hash_key key1 , dict_hash_key key2)
{
	/*printf("key 1: %ld\t key2: %ld\n", return_key(key1), return_key(key2));*/
	if((size_t)return_key(key1) < (size_t)return_key(key2)) return -1;
	if((size_t)return_key(key1) > (size_t)return_key(key2)) return 1;
	return 0;

}

size_t dict_hash_func(dict_hash_key key)
{
	size_t result = 0;
	char *word = key;
	char ch = 0;
	int i = 0;

	for(i = 0, result = 0; word[i]!='\0'; ++i)
	{
		result = result + word[i];
		result = result + (result << 8);
		result = result ^ (result >> 1);
	}

	result = result + (result << 3);
	result = result ^ (result >> 20);
	result = result + (result << 31);
	
	
	return result;
}

dict_hash_t* init_dictionary(int* fd)
{
	struct stat buf;
    fstat(*fd, &buf);
	int size = buf.st_size;

 	dict_hash_t* new_table = NULL;

	new_table = dict_hash_create(1024, &dict_hash_cmp, &dict_hash_func);
		
	

	int i = 0, j = 0, m = 0;
	char ch = 0;
	printf("%d", size);
    char *words[99171];
	
	/*for(;size!=0; --size)
	{


		do
		{
			words[m] = malloc(sizeof(char)*20);
			memset(words[m], 0, sizeof(char)*20);
			read(*fd, &ch, 1);
			words[m][i] = ch;
			++i;
		} while(ch!='\n');
		++m;
		i=0
	}*/


    for(m = 0; m < 99171; ++m)
	{
		words[m] = malloc(sizeof(char)*20);
		memset(words[m], 0, sizeof(char)*20);
		do
		{
			read(*fd, &ch, 1);
			words[m][i] = ch; 
			++i;	
		} while(ch!='\n');

		words[m][i - 1] = '\0';
		printf("\n%s\n", words[m]);
		dict_hash_insert(new_table, words[m] , words[m]);
		i = 0;	
	}

	dict_hash_size(new_table);
	
	return new_table;
	
}

void destroy_dictionary(int fd, dict_hash_t* hash)
{
	dict_hash_destroy(hash);
}

int spell_check (dict_hash_t* hash, char* word)
{
	void * result = NULL;
	result = dict_hash_find(hash, word);
	printf("\nfound word: %s\n", result);
	return 0;
}


