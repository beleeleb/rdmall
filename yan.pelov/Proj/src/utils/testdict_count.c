/*
 * testdict_count.c
 *
 *  Created on: Jan 12, 2015
 *      Author: student
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define FILE_LOCATION "/usr/share/dict/words"

int main()
{
	static const char filename[] = FILE_LOCATION;
	int fd =  open(filename, O_RDONLY);

	int i = 0;
	char ch = 0;

    size_t array[256] = {0};
    int counter = 938849;

    while(--counter)
	{
    	read(fd, &ch, 1);
    	array[(int)(ch)] += 1;
	}

	for(i = 0; i < 256; ++i)
	{
		printf("array[%d]: char: %d count: %lu\n", i ,(char)i, array[i]);
	}

	close(fd);
	return 0;
}
