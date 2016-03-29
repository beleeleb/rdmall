/*
 ============================================================================
 Name        : testonly.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

void* mymalloc(int size)
{
	int * mem = malloc(sizeof(int)+size);
	*mem = sizeof(int) + size;
	return (void*)(mem+1);
}

void myfree(void *ptr)
{
	int* mem = (int*)ptr - 1;
	int size = *mem;
	free((void*)mem, size);
}

int main(void) {
	void * ptr = NULL;
	ptr = mymalloc(20);

	myfree(ptr);
	return EXIT_SUCCESS;
}
