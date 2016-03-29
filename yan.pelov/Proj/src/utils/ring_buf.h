#include <stdlib.h>

#ifndef __RING_BUF_H__
#define  __RING_BUF_H__

typedef void* data_t;
typedef data_t* iterator;

struct rbuf;
typedef struct rbuf rbuf_t;

/*	Creates new circular buffer of elements of type data_t.
	Parameters: 
 	 size: Desired size of buffer.
	Returns: A pointer to the circular buffer */
rbuf_t* rbuf_create (size_t size);

/*	Destroys given circular buffer.
	Parameters: 
 	 rbuffer: Circular buffer to be destroyed.
	Returns: Nothing. */
void rbuf_destroy (rbuf_t* rbuffer);

/*	Measures circular buffer size.
	Parameters: 
 	 rbuffer: Circular buffer to be measured.
	Returns: Circular buffer size. */
size_t rbuf_capacity (rbuf_t* rbuffer);

/*	Measures circular buffer units in use.
	Parameters: 
 	 rbuffer: Circular buffer to be measured.
	Returns: Number of units of buffer in use. */
size_t rbuf_in_use(rbuf_t* rbuffer);


/*	Measures available circular buffer units.
	Parameters: 
 	 rbuffer: Circular buffer to be measured.
	Returns: Number of units of buffer available.	 */
size_t rbuf_available(rbuf_t* rbuffer);

/*	Writes a given data after the last element in
 the buffer.
	Parameters: 
 	 rbuffer: Circular buffer to write into.
	 data: data to be written.
	Returns: success/ failure. 					 	*/
int rbuf_write(rbuf_t* rbuffer, void *data);

/*	Reads data from the start of the buffer and erase it from the buffer.
	Parameters: 
 	 rbuffer: Circular buffer to be read from.
	Returns: the data of the removed element. 
		(rbuffer must contain at least 1 element)		 */
data_t rbuf_read(rbuf_t* rbuffer);

/*	Erases a specific element from the buffer.
	Parameters: 
 	 rbuffer: Circular buffer to erase from.
	 iter: pointer to a specific element to be removed.
	Returns: the data of the removed element.
		(rbuffer must contain at least 1 element) 		 */
data_t rbuf_erase(rbuf_t* rbuffer, iterator iter);

/*	returns data from a specific index in the buffer (doesn't erase the element).
	Parameters: 
	 iter: pointer to a specific element.
	Returns: data from a specific element in the buffer. */
data_t rbuf_get_data(iterator iter);

/* returns iterator to the first element in the rbuffer.
	Parameters:
	  rbuffer: Circular buffer.
	Returns: iterator to the first element in the rbuffer.
	(in case the buffer is empty, returns NULL).		*/
iterator rbuf_start(rbuf_t* rbuffer);

/* returns iterator to the last element in the rbuffer.
	Parameters:
	  rbuffer: Circular buffer.
	Returns: iterator to the last element in the rbuffer.
	(in case the buffer is empty, returns NULL).		*/
iterator rbuf_end(rbuf_t* rbuffer);

/* returns iterator to the next element in the rbuffer.
	Parameters:
	  rbuffer: Circular buffer.
	Returns: iterator to the next element in the rbuffer.
	(in case the buffer is empty, returns NULL).		*/
iterator rbuf_next(rbuf_t* rbuffer, iterator iter);

/* returns iterator to the previous element in the rbuffer.
	Parameters:
	  rbuffer: Circular buffer.
	Returns: iterator to the previous element in the rbuffer.
	(in case the buffer is empty, returns NULL).		*/
iterator rbuf_prev(rbuf_t* rbuffer, iterator iter);

#endif
