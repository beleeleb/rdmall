/*
 * testmyclient.c
 *
 *  Created on: Jan 12, 2015
 *      Author: student
 */
#include "wd.h"

#include <stdio.h>

int main()
{
	handle_t* ptr = NULL;
	ptr = create_wd();

	int i;

	for(i = 0; i < 90000; ++i)
	{
		printf("I am client\n");
		sleep(1);
	}

	destroy_wd(ptr);
	return 0;
}
