/*
 * testshmvs.c
 *
 *  Created on: Jan 1, 2015
 *      Author: student
 */
#include "shmvs.h"
#include "vmb.h"

int main()
{

	shmvid_t myid = 0;
	shmvs_p myptr = NULL;
	void * ptr1 = NULL;
	void * ptr2 = NULL;
	myptr = shmvs_create (200, "y.txt" , 20);
	ptr1 = shmvs_alloc(myptr, 100);
	ptr2 = shmvs_alloc(myptr, 40);
	shmvs_free(ptr1);
	ptr2 = shmvs_alloc(myptr, 60);
	ptr1 = shmvs_alloc(myptr, 10);
	shmvs_free(ptr1);
	shmvs_free(ptr2);
	ptr1 = shmvs_alloc(myptr, 30);
	shmvs_free(ptr1);
	shmvs_destroy(myptr);

	return 0;
}

