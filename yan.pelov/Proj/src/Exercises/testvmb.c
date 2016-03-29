
#include "vmb.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifdef DEBUG
#include "dbgmode.h"
#endif

int main()
{
	vmb_p seg_ptr = NULL;
	seg_ptr = (vmb_p)malloc(sizeof(char)*200);
	memset(seg_ptr, 0 , sizeof(char)*200);
	seg_ptr = vmb_init(seg_ptr, 200);
	vmb_iter ptr_1 = NULL;
	ptr_1 = vmb_alloc(seg_ptr, 30);
	vmb_iter ptr_2 = NULL;
	ptr_2 = vmb_alloc(seg_ptr, 7);
	vmb_iter ptr_3 = NULL;
	ptr_3 = vmb_alloc(seg_ptr, 40);
	vmb_free(ptr_1);
	ptr_1 = vmb_alloc(seg_ptr, 30);
	vmb_free(ptr_2);
	vmb_free(ptr_3);
	ptr_3 = vmb_alloc(seg_ptr, 59);
	ptr_2 = vmb_alloc(seg_ptr, 27);

#ifdef DEBUG
	vmb_iter beg_iter = vmb_begin(seg_ptr);
	vmb_iter end_iter = vmb_end(seg_ptr);
	vmb_iter next_iter = vmb_next(ptr_1);
	next_iter = vmb_next(ptr_2);
	next_iter = vmb_next(ptr_3);
	next_iter = vmb_prev(ptr_3);
	next_iter = vmb_prev(ptr_2);
	next_iter = vmb_prev(ptr_1);
#endif

	printf("NO SEG FAULT\n");
	printf("ptr_1: %p\nptr_2: %p\nptr_3: %p\n", ptr_1, ptr_2, ptr_3);

	return 0;
}
