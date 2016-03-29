#include "shmfs.h"
#include <semaphore.h>
#include <sys/types.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <sys/types.h>
#include "fmb_alloc.h"

int main()
{
	shmid_t myid = 0;
	shmfs_p myptr = NULL;
	myptr = shmfs_create (5, 19, "q.txt" , 20);
	/*myptr = shmfs_attach (myid);
	myptr = shmfs_attach (myid);*/
	void* data_ptr = shmfs_alloc(myptr);
	void* data_ptr2 = shmfs_alloc(myptr);
	void* data_ptr3 = shmfs_alloc(myptr);
	void* data_ptr4 = shmfs_alloc(myptr);
	void* data_ptr5 = shmfs_alloc(myptr);
	void* data_ptr6 = shmfs_alloc(myptr);
	shmfs_free(data_ptr2);
	shmfs_free(data_ptr3);
	shmfs_free(data_ptr5);
	shmfs_free(data_ptr);
	shmfs_free(data_ptr4);
	shmfs_destroy(myptr);
	return 0;
}
