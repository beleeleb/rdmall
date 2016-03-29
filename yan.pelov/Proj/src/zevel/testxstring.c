#include <stdio.h>
#include <string.h>
#include "xstring.h"
#include<stdlib.h>

int main(int argc, char *argv[], char *evm[])
{

char s1[] = "bbbb";
char s2[] = "hhhhhhhh";
char *ret;

printf("xstrnlen: %ld\n", xstrnlen(s1, 4));

printf("strncmp: %d\n", strncmp(s1,s2,5)); 
printf("xstrncmp: %d\n", xstrncmp(s1, s2,5));

char s14[] = "bbhhhh";
char s15[] = "bbbb";

strcpy (s14, s15);
printf("strcpy:%s\t%s\n", s14, s15);

char s16[] = "bbhhhh";
char s17[] = "bbbb";

xstrcpy (s16, s17);
printf("xstrcpy:%s\t%s\n", s16, s17);

strncpy (s1, s2, 3);

printf("strncpy: %s\t%s\n", s1, s2);

char s3[] = "bbbb";
char s4[] = "hhhhhhhh";

xstrncpy (s3, s4, 3);
printf("xstrncpy:%s\t%s\n", s3, s4);

char s5[] = "TutorialstPointggg";
char s6[] = "Point";

ret = strstr(s5, s6);
printf("strstr: %s\n", ret);

char s7[] = "TutorialstPointggg";
char s8[] = "Point";

ret = xstrstr (s7, s8);
printf("xstrstr:%s\n", ret);

char s9[] = "TutorialstPointggg";
char s10[] = "Point";

ret = xstrnstr (s9, s10, 12);
printf("xstrnstr:%s\n", ret);

char s11[] = "This is source";
char s12[] = "This is destination";
char s13[] = "KAZABLANCA";

printf("xstrcat:%s\n", xstrcat(s11,s12));

printf("xstrncat:%s\n", xstrncat(s11,s13,5));

char *s20 = NULL;

s20 = xstrdup(s13);

printf("xstrdup:%s\n", s20);

free(s20);

char *s21 = NULL;

s21 = xstrndup(s13, 5);

printf("xstrdup:%s\n", s21);

free(s21);

char *s22 = "aaabbbcccddd555abbbccddff";

char *s23 = "bcwa";

printf("strspn:%ld\n", strspn(s22, s23));

printf("xstrspn:%ld\n", xstrspn(s22, s23));

char *s24 = "abbbccddff";

char *s25 = "bca";

printf("strspn:%ld\n", strcspn(s24, s25));

/*printf("xstrspn:%ld\n", xstrcspn(s22, s25));*/

return 0;

}

 
