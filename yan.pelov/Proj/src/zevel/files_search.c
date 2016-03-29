#include "files_search.h"
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>



/*pseudo code: 
lines 26 - 51 : this part of code is intended to change the terminal status and stop the recursive search when the user inserts new chars while the recursive search is going on. in that case, the processing start all over again.

lines 24 - 27: intialize the variable that will be used in the program.

lines 31 - 64: The main part of the program that deal with user's input. the program exits upon ESC press, clears screen upon Enter press, and do a recursive search upon any other keyboard hit.
In general, the input is limited to 30 chars.

line 71: free the ch variable which was needed for the user's input.

line 72: reset the terminal to its original state.

*/

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}

int rec_search(char* str, char* dirname, int *counter)
{

	DIR* dirp = opendir(dirname);
	if(dirp == NULL) return 0;

	struct dirent * dp = NULL;
    
	while((dp = readdir(dirp)) != NULL)
	{
		
		char* temp = malloc(sizeof(char) * 500);
		memset(temp, 0, sizeof(char) * 500);

		if 	((dp->d_type == 4) && ((strcmp(dp->d_name, "."))) && ((strcmp(dp->d_name, ".."))) )
		{
			
			temp = strcat(temp, dirname);
			temp = strcat(temp, dp->d_name);
			temp = strcat(temp, "/");
			/*printf("%s\n", temp);*/

			if(kbhit())
			{
				free(temp);
				temp = NULL;
				closedir(dirp);
				return 0;
			}
			rec_search(str, temp, counter); /*check return value*/
		}


		else 
		{
			if(strncmp(dp->d_name, str, strlen(str)) == 0 )
			{
				++(*counter);
			/*	printf("counter: %d\n", *counter);  */

				if(*counter <= 10) 
				{
						printf("\nffffffffffffffffffffffffffff\n");
				 printf("\n\t***%s***", dp->d_name);
				}
			}
		}
	free(temp);
	temp = NULL;
	} 	

	closedir(dirp);
	return 0;
}
