#include "mem_check.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rec_check(int depth)
{
    static int var1;
    int var2;
    int *ptr = NULL;
    ptr = (int*)malloc(sizeof(int));
    
    printf("var1: %d, var2: %d, ptr address: %p, ptr value: %d\n", var1, var2, ptr, *ptr);
    
    var1 = 0;
    var2 = 0;
    ptr = &var1;
    
    printf("var1: %d, var2: %d, ptr address: %p, ptr value: %d\n", var1, var2, ptr, *ptr);

    
}
