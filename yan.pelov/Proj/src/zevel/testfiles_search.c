#include "files_search.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#define STDIN 0

/*pseudo code: 
lines 16 - 20: this part of code is intended to change the terminal status so that it would be possible to allow processing while typing. In our case, doing the recursive search while the user is typing his keys.

lines 24 - 27: intialize the variable that will be used in the program.

lines 31 - 64: The main part of the program that deal with user's input. the program exits upon ESC press, clears screen upon Enter press, and do a recursive search upon any other keyboard hit.
In general, the input is limited to 30 chars.

line 71: free the ch variable which was needed for the user's input.

line 72: reset the terminal to its original state.

*/

int main(int argc, const char * argv[]) {

    struct termios oldt, newt;			
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
    newt.c_lflag &= ~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
 
	int i = 0;
	int counter = 0;
    char* ch = malloc(sizeof(char)*30);
	memset(ch, 0, sizeof(char)*30);
    
	while((ch[i] = getchar()) != 27)
	{
	system("clear"); 
	/*printf("%s", ch);*/

	if(ch[i] == 10)
	{
			memset(ch, 0, sizeof(char)*20);
			i = 0;
			system("clear");

			continue;
	}


	if((ch[i] == 127))
	{
			if(i == 0) 
			{
				continue;
			}
			
			ch[i] = '\0';
			ch[i-1] = '\0';
			i = i - 2;
	}

	printf("Search: %s", ch);

	++i;
	rec_search(ch, "/", &counter);
	
	printf("\n\t\tcounter: %d\n", counter);
	counter = 0;
    }
	


	free(ch);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}

