#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "stack.h"
#include "utils.h"

#define MYSIZE 50

int main(int argc, char ** argv, char **evm)
{

	stack *new_stack = stack_create(MYSIZE);

	void ** new_data = NULL;

	new_data = (void **)malloc(sizeof(void *)*10);

	memset(new_data, 0, sizeof(void *)*10);
	
	new_data[0] = (char *)'a';
	new_data[1] = (char *)'b';
	new_data[2] = (char *)'c';
	new_data[3] = (char *)'d';
	new_data[4] = (char *)'e';
	new_data[5] = (char *)'f';
	new_data[6] = (char *)'h';
	new_data[7] = (char *)'j';
	new_data[8] = (char *)'k';
	new_data[9] = (char *)'l';
	new_data[10] = (char *)'m';


	stack_push(new_stack, new_data[0]);
	stack_push(new_stack, new_data[1]);
	stack_push(new_stack, new_data[2]);
	stack_push(new_stack, new_data[3]);
	stack_push(new_stack, new_data[4]);
	stack_push(new_stack, new_data[5]);
	stack_push(new_stack, new_data[6]);
	stack_push(new_stack, new_data[7]);
	stack_push(new_stack, new_data[8]);
	stack_push(new_stack, new_data[9]);
	stack_push(new_stack, new_data[10]);
	stack_push(new_stack, new_data[11]);

    print_stack(new_stack);
	

	
	free(new_data);

	stack_destroy(new_stack);

	return 0;

}
