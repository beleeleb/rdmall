#ifndef __SORTS_H__
#define __SORTS_H__
#include "sorts_types.h"

/*	xxx_sort.
	Parameters: 
 	 data: pointer to the array.
 	 n_members: Number of elements in array.
 	 member_sz: size (in bytes) of one of the members in the array.
 	 int(*cmp)(void*, void*): compare function.
	Returns: N/A. 				
*/

void bubble_sort(void* data, size_t n_members,
		   size_t member_sz, cmp cmp_f);

void merge_sort(void* data, size_t n_members,
                size_t member_sz, cmp cmp_f);

void radix_sort(void* data, size_t n_members,
		  size_t member_sz, cmp cmp_f);


void insertion_sort(void* data, size_t n_members,
		       size_t member_sz, cmp cmp_f);


void bucket_sort(void* data, size_t n_members,
		    size_t member_sz, cmp cmp_f);

void quick_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f);

void heap_sort(void* data, size_t n_members, size_t member_sz, cmp cmp_f);


#endif /* __SORTS_H__ */
