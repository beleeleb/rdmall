#ifndef _TARGIL1_H
#define _TARGIL1_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef enum direction {
right, left
} direct_t;

int endian(void);

unsigned int flip(unsigned int val);

unsigned char byteflip(unsigned char mirror);

unsigned short func(unsigned short s_num, unsigned char *p);

unsigned int func2(unsigned int ui_num, unsigned char *p);

unsigned long func3(unsigned long l_num, unsigned char *p);

unsigned char byte_one_count(unsigned char ch); 

unsigned char short_one_count(unsigned short sh);

unsigned char long_one_count(unsigned long lh);

void lookup(unsigned char *p);

unsigned char rl_shift_byte(unsigned char src, unsigned char shift_num, direct_t flag);

void lookup_table(void);

#endif
