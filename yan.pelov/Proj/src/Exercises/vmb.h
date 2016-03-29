/*
 * vmb.h
 *
 *  Created on: Dec 23, 2014
 *      Author: student
 */

#ifndef __VMB_H__
#define __VMB_H__

#include <stdlib.h>

typedef void* vmb_p; /* pointer to segment */

typedef void* vmb_iter; /* pointer to a block */

/*	Receives: Pointer to uninitialized segement, required segment size, .

Returns: Pointer to initialized segment. */

vmb_p vmb_init(vmb_p seg_ptr, size_t seg_size);

/*	Receives: Pointer to the segment, required block size.

Returns: Pointer to allocated block on success, or NULL on fail. */

vmb_iter vmb_alloc(vmb_p seg_ptr, size_t block_size);

/*	Receives: Pointer to block to be freed.

Returns: void. */

void vmb_free(vmb_iter block_ptr);


#endif /* __VMB_H__ */


