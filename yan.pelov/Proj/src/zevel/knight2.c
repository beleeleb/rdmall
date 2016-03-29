#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** make_board();

int tour(size_t *array, int x, int y, int num_move);

void display(size_t *array);


int main()
{
	size_t *array = NULL;
	tour(array, 0, 0, 0);
	/*display(array);*/
	return 0;
}

int tour(size_t *array, int x, int y, int num_move)
{
		
	*array = *array & (1 << (x*8 + y));

	printf("%ld", (size_t)array);
	/*
    if(num_move < 64)
	{
		if((x < 6 && y < 7) && board[x+2][y+1] == 0)
		{
			tour(board, x + 2 , y + 1, num_move);
		    board[x+2][y+1] = ++num_move;
			return 0;
		}

		if((x > 1 && y < 7) && board[x-2][y+1] == 0)
		{
			tour(board, x - 2 , y + 1, num_move);
		    board[x-2][y+1] = ++num_move;
			return 0;
		}

		if((x < 7 && y < 6) && board[x+1][y+2] == 0)
		{
			tour(board, x + 1 , y + 2, num_move);
			board[x+1][y+2] = ++num_move;
			return 0;
		}

		if((x > 0 && y < 6) && board[x-1][y+2] == 0)
		{
			tour(board, x - 1 , y + 2, num_move);
			board[x-1][y+2] = ++num_move;
			return 0;
		}
		
		if((x > 1 && y > 0) && board[x-2][y-1] == 0)
		{
	  		tour(board, x - 2 , y - 1, num_move);
			board[x-2][y-1] = ++num_move;
			return 0;
		}

		if((x > 0 && y > 1) && board[x-1][y-2] == 0)
		{
			tour(board, x - 1 , y - 2, num_move);
			board[x-1][y-2] = ++num_move;
			return 0;
		}

		if((x < 7 && y > 1) && board[x+1][y-2] == 0)
		{
			tour(board, x + 1 , y - 2, num_move);
			board[x+1][y-2] = ++num_move;
			return 0;
		}

		if((x < 6 && y > 0) && board[x+2][y-1] == 0)
		{
			tour(board, x + 2 , y - 1, num_move);
			board[x+2][y-1] = ++num_move;
			return 0;
		}
	}

    board[x][y] = 0;    */
}

void display(size_t *array)
{
	/*int x = 0, y = 0;

	printf("\n");

	for(x = 0; x < 8; x++)
	{
		for(y = 0; y < 8; y++)
		{
			printf("\t%d", board[x][y]);
		}
	printf("\n\n");
	}

	printf("\n");

	int i = 0;
	size_t array = 0;
	for(i = 0; i < 64; i++)
	{
		printf("%ld ", 1 << i);
	}*/
}
