#include <stdio.h>
/* This program is intended to examine how .so works and how different vars are set in the VM */
int var1;
int var2 = 0;
static int var3;
static int var4 = 0;

void myfoo(void)
{
	int var5;
	int var6 = 1;
	static int var7;
	static int var8 = 1;
    printf("hellffffo\n");
}
