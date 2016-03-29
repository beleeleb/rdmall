#include <stdio.h>

int num_cmp(void * num1, void* num2);
typedef int(*cmp)(void*, void*);
int main()
{
	int num[]  = {9 , 3, 6, 7};
	cmp my_cmp = &num_cmp;
}

int num_cmp(void * num1, void* num2)
{

	return(*(int*)num1 - *(int*)num2);
}
