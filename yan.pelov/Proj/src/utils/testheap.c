#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

extern void print_heap_tree(heap_t* heap);
extern int print_all_heap(heap_t* heap);
int compy(void* num1, void* num2);

extern void print_heap(heap_t* heap);

int main(int argc, char **argv, char **epvm)
{
	heap_t* new_heap = NULL;
	new_heap = heap_create(&compy);

	heap_insert(new_heap, (void*)100);


	/*heap_insert(new_heap, (void*)200);

	heap_insert(new_heap, (void*)300);

	heap_insert(new_heap, (void*)400);
	heap_insert(new_heap, (void*)800);*/
	heap_insert(new_heap, (void*)70);
	heap_insert(new_heap, (void*)900);
	heap_insert(new_heap, (void*)60);

	heap_insert(new_heap, (void*)300);

heap_insert(new_heap, (void*)150);

heap_insert(new_heap, (void*)160);

	heap_insert(new_heap, (void*)50);

	print_heap_tree(new_heap);

	void **array = (void*)malloc(sizeof(size_t) * 8);
		
	*(array+0) = 0;
	*(array+1) = 7;
	*(array+2) = 8;
	*(array+3) = 2;
	*(array+4) = 2;
	*(array+5) = 8;
	*(array+6) = 1;
	*(array+7) = 0;

	heap_t* new_heap2 = NULL;

	new_heap2 = array_to_heap(array , 8);

	heap_to_array(new_heap);

	printf("\n");

	print_heap_tree(new_heap2);
	heap_data data = heap_find(new_heap, (void*)70);
	printf("found data: %d\n\n", data );

	/*heap_remove( new_heap, (void*)900);*/

	/*print_heap_tree(new_heap);*/

	print_heap(new_heap2);

	return 0;
}

int compy(void* num1, void* num2)
{
	if(num1 < num2) return -1;
	if(num1 > num2) return 1;
	return 0;
}

