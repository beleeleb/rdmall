/*
 * dbgmode.h
 *
 *  Created on: Dec 23, 2014
 *      Author: student
 */

#ifndef __DBGMODE_H__
#define __DBGMODE_H__

/*	Receives: Pointer to segment.

Returns: Pointer to first allocated block on success, or NULL on fail. */



vmb_iter vmb_begin(vmb_p seg_ptr);

/*	Receives: Pointer to segment.

Returns: Pointer to last allocated block on success, or NULL on fail. */

vmb_iter vmb_end(vmb_p seg_ptr);

/*	Receives: Pointer to block.

Returns: Pointer to next allocated block on success, or NULL on fail. */

vmb_iter vmb_next(vmb_iter block_ptr);

/*	Receives: Pointer to block.

Returns: Pointer to previous allocated block on success, or NULL on fail. */

vmb_iter vmb_prev(vmb_iter block_ptr);

/*	Receives: Pointer to block.

Returns: Pointer to block casted to void*. */

void* vmb_get(vmb_iter block_ptr);


#endif /* __DBGMODE_H__ */
