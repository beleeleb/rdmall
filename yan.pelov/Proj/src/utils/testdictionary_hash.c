#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "dictionary_hash.h"
#include "dict_hash.h"

#define FILE_LOCATION "/usr/share/dict/words"

int main(int argc, char **argv, char **epvm)
{
	static const char filename[] = FILE_LOCATION;
    int fd =  open(filename, O_RDONLY);

	dict_hash_t* new_table = NULL;
	
	new_table = init_dictionary(&fd);
	
	spell_check(new_table, "detail");

	destroy_dictionary(&fd, new_table);

	close(fd);

	return 0;
}
