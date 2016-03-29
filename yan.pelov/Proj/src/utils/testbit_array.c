#include <stdio.h>
#include "targil1.h"
#define NUM_BITS_INT 32
#define NUM 0xFE


int main()

{
	
	/*if(endian() == 1) printf("\nLittle Endian\n");
		else printf("\nBig Endian\n");
	
	unsigned int i_num = NUM, ui_num = 0xFFAA0011, j;
	unsigned char *p, *p2;
	unsigned short s_num = 0xFFAA;
	unsigned long l_num = 0xFFFFDDDDAAAAEEEE;
	
	p=malloc(sizeof(char) * 256);
	
	memset(p,0,sizeof(char) * 256);	
		
	printf("\n");

	printf("The reversed new value is %u", flip(i_num));

	printf("\n");

	for(j = 0; j < 256; j++)
	{
	p[j]=byteflip(j);
	}

	printf("\n0x%X",func(s_num, p));
	printf("\n0x%X",func2(ui_num, p));
	printf("\n0x%lX", func3(l_num, p));
	printf("\n%u", byte_one_count(0xEE));
	lookup(p2);
	printf("\n%d\n", short_one_count(0xEEEE));
	printf("%d\n", long_one_count(0xEEEEEEEE));
	printf("%d\n", rl_shift_byte(0xEF,2,left));*/

	lookup_table();

	
	return 0;
}

