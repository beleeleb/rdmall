#include "dlist_safe.h"
#include <stdio.h>
#include <pthread.h> /* for threads & mutex */
#include <string.h> /* for memset */
#include <sys/types.h> /* for open() */
#include <sys/stat.h> /* for open() */
#include <fcntl.h> /* for open() */
#include <unistd.h> /* for read() */

#define FILE_LOCATION "/usr/share/dict/words"
static char ** init_dict(void);
static void free_dict(char ** words);
int cmp_str(dl_data data, void* param);

int main()
{

	safe_dlist_t* new_list = NULL;
	new_list = sdlist_create();
	safe_iter_t * ptr = NULL;
	safe_iter_t * find_res = NULL;
	ptr = sdlist_create_iter(new_list);
	char ** words = init_dict();
	int i;
	ptr = sdlist_prev(sdlist_end(ptr));
	sdlist_insert_after(ptr, (void*)words[0]);

	for(i = 1; i < 5; ++i)
	{
		sdlist_insert_after(ptr, (void*)words[i]);
	}

	print_me(new_list);
	printf("data: %s\t data2: %s\n\n", sdlist_get_data(sdlist_next(sdlist_begin(ptr))), sdlist_get_data(sdlist_prev(sdlist_end(ptr))));
	sdlist_push_front(new_list, (void*)"ggg");
	sdlist_push_back(new_list, (void*)"fff");
	print_me(new_list);
	sdlist_pop_front(new_list);
	sdlist_pop_back(new_list);
	printf("\n");
	print_me(new_list);
	sdlist_insert_after(sdlist_next(sdlist_begin(ptr)), (void*)"ddd");
	print_me(new_list);
	sdlist_remove(ptr);
	printf("\n");
	print_me(new_list);
	printf("\nsize: %ld\tis empty: %d\n", sdlist_size(new_list), sdlist_is_empty(new_list));
	find_res = sdlist_find(sdlist_next(sdlist_next(sdlist_begin(ptr))), sdlist_end(ptr), &cmp_str, (void*)"A");
	printf("result is: %s\n", sdlist_get_data(find_res));
	sdlist_destroy_iter(ptr);
	free_dict(words);
	sdlist_destroy(new_list);

	return 0;
}

int cmp_str(dl_data data, void* param)
{
	return strcmp((char*)data, (char*)param);
}

static char ** init_dict(void)
{
	static const char filename[] = FILE_LOCATION;
	char ** words = NULL;
	int fd =  open(filename, O_RDONLY);
	char ch = 0;
	words = (char**)malloc(sizeof(char*) * 99171);
	memset(words, 0, sizeof(char*) * 99171);
	int i = 0, m = 0;

	for(m = 0; m < 99171; ++m)
	{
		words[m] = malloc(sizeof(char) * 30);
		memset(words[m], 0, sizeof(char) * 30);

		do
		{
			read(fd, &ch, 1);
			words[m][i] = ch;
			++i;
		} while(ch!='\n');

		words[m][i - 1] = '\0';

		/*printf("\n%s\n", words[m]);*/
		i = 0;
	}

	close(fd);

	return words;
}

static void free_dict(char ** words)
{
	int m;

	for(m = 0; m < 99171; ++m)
	{
		memset(words[m], 0, sizeof(char) * 30);
		free(words[m]);
		words[m] = NULL;
	}

	memset(words, 0, sizeof(char*) * 99171);

	free(words);

	words = NULL;
}
