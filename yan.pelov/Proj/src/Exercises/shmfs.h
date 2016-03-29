/*
 * shmfsalloc.h (Implement a S.M. with fixed size memory blocks.)
 *
 *  Created on: Dec 30, 2014
 *      Author: RD3
 */

#ifndef __SHMFS_H__
#define __SHMFS_H__


#include <stdlib.h>

/*  typedefs  */
typedef void* shmfs_p;    /* pointer to shared memory segment (not including
							 shared_memory header) */
typedef int shmid_t;    /* shared memory identifier  */

/*
 *  Create a Shared Memory segment with fixed size memory blocks.
 *    parameters:
 *			n_blocks - number of blocks to be created.
 *			block_size - size of each block.
 *			path - convert a path identifier to a shared memory key (must be
 *			existing file)
 *			path_id - must be nonzero.
 *    return value:  shared memory identifier
 */

shmfs_p shmfs_create (size_t n_blocks, size_t block_size, char * id, unsigned short int max_clients/*, char* path ,int path_id*/);

/*
 *  destroy a Shared Memory with fixed size memory blocks.
 *    parameters:
 *		 shmfs - a shared memory segment id with fixed sized block
 *   return value: void
 */
void shmfs_destroy (shmfs_p seg);


/*
 *  attach to the shared memory segment with fixed size memory blocks.
 *    parameters:
 *	 		shmfs - a shared memory segment id with fixed sized block
 *    return value:  Success :a shared memory segment address
 *					Fail: NULL.
 */
shmfs_p shmfs_attach (shmid_t shmid);


/*
 *  detach to the S.M. with fixed size memory blocks.
 *    parameters:
 *		 shmfs - a shared memory segment id with fixed sized block
 *   	 return value:  Success: 0.
 *						Fail: -1.
 */
int shmfs_detach (shmfs_p seg);


/*
 *  Allocates a fixed size memory block from the S.M.
 *    parameters:
 *			seg - a shared memory segment address
 *    return value: Success: adress of fixed size block data.
 *					Fail: NULL
 */
void* shmfs_alloc (shmfs_p seg);


/*
 *  Allocates a fixed size memory block from the S.M.
 *    parameters:
 *			seg - a shared memory segment address
 *    return value:  Adress of fixed size block data..
 */

void shmfs_free (void* data);

/*
 *  Frees a fixed size memory block from the S.M.
 *    parameters:
 *			data -  adress of fixed size block data.
 *    return value:  void.
 */

#endif /* SHMFS_H_ */
