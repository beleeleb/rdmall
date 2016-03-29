/*
 * fmb_alloc.h
 *
 *  Created on: Dec 28, 2014
 *      Author: galizorea
 */

#ifndef __FMB_ALLOC_H__
#define __FMB_ALLOC_H__

#include <stdlib.h>

typedef void* fmb_p; /* pointer to segment */

/* Receives: Pointer to uninitialized segment, required segment size, .

Returns: Pointer to initialized segment. */

int fmb_init(fmb_p seg_ptr, size_t seg_size, size_t block_size);

/* Receives: Pointer to the segment, required block size.

Returns: Pointer to allocated block on success, or NULL on fail. */

void* fmb_alloc(fmb_p seg_ptr);

/* Receives: Pointer to block to be freed.

Returns: void. */

void vmb_free(void* block_ptr);

size_t calc_me(size_t n_blocks, size_t block_size);

#endif /* __FMB_ALLOC_H__ */
