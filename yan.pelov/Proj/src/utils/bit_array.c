#include "targil1.h"

int endian(void)
{
	int x = 3;
	int *p = &x;

	if(((char*)p)[0]==3)
	return 1;
		else return 0;
}

unsigned int flip(unsigned int val)
{

    unsigned int i = 0, rev = 0, bit=0;

	for(i = 0; i < (sizeof(val)*8); i++)
    {

        bit = val & 1;

        val = val >> 1;

		rev = rev << 1;

        rev = rev ^ bit;	
	}
	
	return rev;
}

unsigned char byteflip(unsigned char mirror)
{
	
		mirror=((0xF0&mirror)>>4)|((~0xF0&mirror)<<4);
		mirror=((0xCC&mirror)>>2)|((~0xCC&mirror)<<2);
		mirror=((0xAA&mirror)>>1)|((~0xAA&mirror)<<1);

		return mirror;
}

unsigned short func(unsigned short s_num, unsigned char *p)
{
	unsigned short tmp_s = 0;
	unsigned char ch[2];
	
	ch[0] = p[s_num&0xFF];
	ch[1] = p[s_num >> 8];

	tmp_s = (ch[0] << 8 )| (ch[1]);
	
	return tmp_s;

}

unsigned int func2(unsigned int ui_num, unsigned char *p)
{
	unsigned int tmp_i;
	unsigned char ch[4]={0,0,0,0};
	
	ch[0] = p[(ui_num & 0xFF)];
	ch[1] = p[(ui_num >> 8)&0xFF];
	ch[2] = p[(ui_num >> 16)&0xFF];
	ch[3] = p[(ui_num >> 24)&0xFF];
	
	tmp_i = ((ch[0] << 24)| (ch[3])) | ((ch[1] << 16) | (ch[2] << 8));
		
	return tmp_i;

}

unsigned long func3(unsigned long l_num, unsigned char *p)
{

	unsigned long l_tmp=0;
	unsigned long i_tmp[2]={0,0};
	

	i_tmp[0] = func2(l_num&0xFFFFFFFF, p);
	i_tmp[1] = func2((l_num>>32)&0xFFFFFFFF, p);
 	
	l_tmp = (i_tmp[0] << 32) | (i_tmp[1]);

	return l_tmp;

}

unsigned char byte_one_count(unsigned char ch)
{

	int i;
	unsigned char sum=0, tmp;

	for(i=0;i<8;i++)
	{
	tmp=ch&1;
		
		if(tmp==1)
		sum++;

	ch=ch>>1;
	}

	return sum;

}

unsigned char short_one_count(unsigned short sh)
{
	unsigned char ch[2];
	
	ch[0] = byte_one_count(sh&0xFF);
    ch[1] = byte_one_count(sh >> 8);
	
	return ch[0]+ch[1];
}

unsigned char long_one_count(unsigned long lh)
{
	unsigned int ch[2];
	
	
	ch[0] = short_one_count(lh&0xFFFF);
    ch[1] = short_one_count(lh >> 16);
	
	return ch[0]+ch[1];
}

void lookup(unsigned char *p)
{
int j;
	p=malloc(sizeof(char) * 256);
	
	memset(p,0,sizeof(char) * 256);
	
	for(j = 0; j < 256; j++)
	{
	p[j]=byte_one_count(j);
	}
}

unsigned char rl_shift_byte(unsigned char src, unsigned char shift_num, direct_t flag)
{
unsigned char tmp;
	
switch(flag)
	{
	case 0:
			{
					
			        tmp = src >> (7-shift_num);
					src = src << shift_num;
					return (src | tmp);
					break;
			}

	case 1:
		{
					
			        tmp = src << (7-shift_num);
					src = src >> shift_num;
					return (src | tmp);
					break;
		}

	}
	return 0;

}

void lookup_table(void)
{

unsigned int i,j;

unsigned char **p;

	p=(unsigned char **)malloc(sizeof(unsigned char *) * 8);
	memset(p, 0, sizeof(unsigned char *) * 8);


for(j = 0; j < 8; j++)
	{
		p[j]=(unsigned char *)malloc(sizeof(unsigned char)* 256);	
		memset(p[j], 0, sizeof(unsigned char)*256);
	}



for(j = 0; j < 8; j++)
{
	for(i = 0; i < 256; i++)
	{
		p[j][i]=rl_shift_byte(i, j, right);
		
	}
}

	for(j = 0; j < 8; j++)
	{
		for(i=0; i<256; i++)
		{
			printf("p[%u][%u]=%u\n", j,i, p[j][i]);
		}
	}


}

