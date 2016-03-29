#include <stdio.h>
#include "sorts.h"

int num_cmp(void* num1, void* num2);

int main (int argc, char** argv, char** evmp)
{

	int num[] = {20, 8, 1, 21, 90, 100, 2};
	int i;
	cmp my_cmp = &num_cmp;
	/*bubble_sort(num, 7, sizeof(int), my_cmp);*/
	insertion_sort(num , 8, sizeof(int), my_cmp);
	/*bucket_sort(num , 15, sizeof(int), my_cmp);*/
	/*radix_sort(num , 15, sizeof(int), my_cmp);*/
	/*merge_sort(num , 11, sizeof(int), my_cmp);*/

	/*quick_sort(num, 7, sizeof(int), my_cmp);*/
    
    /*heap_sort(num, 7, sizeof(int), my_cmp);*/
	
	for(i = 0; i < 7; i++)
	{
		printf("%d  ", num[i]);
	}

	printf("\n");
	return 0;
}

int num_cmp(void* num1, void* num2)
{
	return (*(int*)num1 - *(int*)num2);
}

