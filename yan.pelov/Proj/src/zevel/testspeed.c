/* this program allows comparing the register and volatile vars and their speed behaviour */
int main(void)
{
	int tmp1 = 0;
	int i = 0;
    register int tmp2 = 0;
    volatile int tmp3 = 0;

    for(i = 0; i < 2000000000; ++i)
    {
	
        tmp1+=1;
        tmp1-=1;
    
      /*  tmp2+=1;
        tmp2-=1;
    
        tmp3+=1;
        tmp3-=1; */
    }

return 0;
}
