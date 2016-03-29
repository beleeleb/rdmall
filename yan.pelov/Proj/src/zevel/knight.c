#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int** make_board();

int tour(int** board, int x, int y, int num_move);

void display(int** board);

#define SIZE 8
int main()
{
	int** new_board = make_board();
	tour(new_board, 4, 4, 1);
	display(new_board);
	return 0;
}

int** make_board()
{
	int** new_board = (int**)malloc(sizeof(int*) * 8);
	memset(new_board, 0, sizeof(int*) * 8);

	int x = 0, y = 0, i = 0;

	for(i = 0; i < 8; i++)
	{
		new_board[i] = (int*)malloc(sizeof(int) * 8);
		memset(new_board[i], 0, sizeof(int) * 8);
	}

	for(x = 0; x < 8; x++)
	{
		for(y = 0; y < 8; y++)
		{
			new_board[x][y] = 0;
		}
	}

	return new_board;
}

int tour(int** board, int x, int y, int num_move)
{
		
    	if (num_move == 2)
		{
			return 1;
		}

		board[x][y] = num_move;
	
		/*if((x < 6 && y < 7) && (board[x+2][y+1] == 0) && (tour(board, x + 2 , y + 1, 1+num_move)))
		{
			printf("f");
			
		  //  board[x+2][y+1] = ++num_move;
			return 1;
		}*/

		if ((x + 2 < SIZE) && (y + 1 < SIZE) && (board[x + 2][y + 1] == 0) &&
        tour(board, x+2, y+1, 1+num_move))
		{
			printf("f");
			return 1;
		}
		
/*
		if((x > 1 && y < 7) && (board[x-2][y+1] == 0) && (tour(board, x - 2 , y + 1, 1+num_move)))
		{
			
		  //  board[x-2][y+1] = ++num_move;
			return 1;
		}*/

		   /* if ((x + 1 < SIZE) && (y + 2 < SIZE) && (board[x + 1][y + 2] == 0) &&
        tour (board, x+1, y+2, 1+num_move)) return 1;

		if((x < 7 && y < 6) && (board[x+1][y+2] == 0) && (tour(board, x + 1, y + 2, 1+num_move)))
		{
			//board[x+1][y+2] = ++num_move;
			return 1;
		}

		if((x > 0 && y < 6) && (board[x-1][y+2] == 0)  && (tour(board, x - 1 , y + 2, 1+num_move)))
		{
			//board[x-1][y+2] = ++num_move;
			return 1;
		}
		
		if((x > 1 && y > 0) && (board[x-2][y-1] == 0) && (tour(board, x - 2 , y - 1, 1+num_move)))
		{
	 
			//board[x-2][y-1] = ++num_move;
			return 1;
		}

		if((x > 0 && y > 1) && (board[x-1][y-2] == 0) && (tour(board, x - 1 , y - 2, 1+num_move)))
		{
			//board[x-1][y-2] = ++num_move;
			return 1;
		}

		if((x < 7 && y > 1) && (board[x+1][y-2] == 0) && (tour(board, x + 1 , y - 2, 1+num_move)))
		{
			
			//board[x+1][y-2] = ++num_move;
			return 1;
		}

		if((x < 6 && y > 0) && (board[x+2][y-1] == 0) && tour(board, x + 2 , y - 1, 1+num_move))
		{
			
			//board[x+2][y-1] = ++num_move;
			return 1;
		}*/
	
/*

	if ((x + 2 < SIZE) && (y + 1 < SIZE) && (board[x + 2][y + 1] == 0) &&
        tour(board, x+2, y+1, 1+num_move)) return 1;
   
    if ((x + 1 < SIZE) && (y + 2 < SIZE) && (board[x + 1][y + 2] == 0) &&
        tour (board, x+1, y+2, 1+num_move)) return 1;
   
    if ((-1 < (x - 2)) && (y + 1 < SIZE) && (board[x - 2][y + 1] == 0) &&
        tour (board, x-2, y+1, 1+num_move)) return 1;
   
    if ( (-1 < (x - 1)) && (y + 2 < SIZE) && (board[x - 1][y + 2] == 0) &&
        tour (board, x-1, y+2, 1+num_move)) return 1;
   
    if ((x + 2 < SIZE) && (-1 < (y - 1)) && (board[x + 2][y - 1] == 0) &&
        tour (board, x+2, y-1, 1+num_move)) return 1;
   
    if ((-1 < (y - 2)) && ((x + 1) < SIZE) && (board[x + 1][y - 2] == 0) &&
        tour (board, x+1, y-2, 1+num_move)) return 1;
   
    if ((-1 < (x - 2)) && (-1 < (y - 1)) && (board[x - 2][y - 1] == 0) &&
        tour (board, x-2, y-1, 1+num_move)) return 1;
   
    if ((-1 < (x - 1)) && (-1 < (y - 2)) && (board[x - 1][y - 2] == 0) &&
         tour (board, x-1, y-2, 1+num_move)) return 1;
*/
    board[x][y] = 0;  
	return 0; 
}

void display(int** board)
{
	int x = 0, y = 0;

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

	/*int i = 0;
	size_t array = 0;
	for(i = 0; i < 64; i++)
	{
		printf("%ld ", 1 << i);
	}*/
}
