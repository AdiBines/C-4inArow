/*final project
Adi Godosoi ID:316413780
Liubov Vasilchuk ID:327248605*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include<math.h>
#define PLAYER1 1
#define PLAYER2 2

typedef enum { FALSE , TRUE }boolean;
int BoardSize(int size);
void BuildBoard(int*** Board, int row, int column);
void PrintBoard(int** Board, int row, int column);
int GetNumber(int Coll,int size);
boolean checkcol(int** Board,int CollOf,int size,int player);
boolean TIE(int** Board, int size);
int GetRow(int** Board, int coll, int size, int player);
int checkWin(int** board, int coll, int row, int player, int size);
void GameStart(int** Board, int size);
void FreeBoard(int*** Board, int size);

int main()
{
	printf("\t4 IN A ROW\n");
	int size = 0;
	int** Board = NULL;
	size=BoardSize(size);
	BuildBoard(&Board, size, size);
	PrintBoard(Board, size, size);
	GameStart(Board, size);
	FreeBoard(&Board, size);
	
	return 0;
}

int BoardSize(size)   //Receives a number for the board size.We chose this size to prevent program blasts
{
	printf("Board size:\n");
	printf("Choose a number for the size of the board, minimum 5:\n");
	do    //checks its integrity
	{
		scanf("%d", &size);
		if (size < 5 )
			printf("Your number is less than 5,Please try again:\n");
	} while (size < 5 );
	return size;
}

void BuildBoard(int*** Board, int row, int column)   //Builds the board of the game
{
	int i, j;
	*Board = (int**)malloc(row * sizeof(int*)); 
	if (*Board == NULL)     // check if the malloc Succeeded for the row
	{
		printf("error");
		return;
	}

	for (i = 0; i < row; ++i)
	{
		(*Board)[i] = (int*)malloc(column * sizeof(int));   
		if (*Board == NULL)  // check if the malloc Succeeded for the column
		{
			printf("error");
			return;
		}
	}

	for (i = 0; i < row; ++i)  // Make empty spaces 
	{
		for (j = 0; j < column; ++j)
		{
		    (*Board)[i][j] = 0;
		}
	}
} 

void PrintBoard(int** Board, int row, int column)  // Print the board in *Recursion*
{
	if (row > 0)
	{
		PrintBoard(Board, row - 1, column); 
		for (int i = 0; i < column; ++i)
			printf("\t%d", Board[row - 1][i]);
		printf("\n");
	}
} 

int GetNumber(int Coll, int size)  // Recives the number for the column and checks if the number fits
{
	printf("Enter number of the column you want to put your coin in :\n"); 
	do // loop for getting a number that fits to the board, if the number doesnt fit the loop continiues
	{
		scanf("%d", &Coll);
		if (Coll < 1 || Coll > size)
			printf("Your number is not good,Please try again:\n");
	} while (Coll < 1 || Coll>size);
	return Coll-1;
}

boolean checkcol(int** Board, int CollOf, int size, int player) // Checks if the row in the column is empty, If yes, put the coin in 
{
	for (int i = size - 1; i >= 0; --i)
	{
		if (Board[i][CollOf] == 0)
		{
			Board[i][CollOf] = player;
			return TRUE;
		}
	}
	return FALSE; // if all the rows of the column are full returns false.
}

boolean TIE(int** Board, int size) // checks if the board totally full and nobody has won
{
	int i, j;
	for (i = 0; i < size ; ++i)
	{
		for (j = 0; j < size ; ++j)
		{
			if (Board[i][j] == 0)
				return FALSE; // the board is not totally full
		}
	}
	return TRUE; // if the board is full, returns true > tie
}

int GetRow(int** Board, int coll,int size ,int player) // gets the last position in the selected row. 
{
	int i = 0;
	for (i; i < size; ++i)
	{
		if (Board[i][coll] == player)
			return i;
	}
	return i;
}

int checkWin(int** board, int coll, int row, int player, int size) // Checks if there are 4 in the row, and if there is a winner
{
	if (row <= (size-4) && board[row + 1][coll] == player && board[row + 2][coll] == player && board[row + 3][coll] == player) // 4 in a row vertically
		return 1; // (size-4) is because if you put the row in vertically the minimum point for the row to start from is size-4
	else
	{
		int count = 1, i, j;
		for (i = coll + 1; i < size; ++i)
		{ // 4 in a row horizontally
			if ( board[row][i] != player )
				break;
			count++;
		}
		for (i = coll - 1; i >= 0; --i)
		{ // 4 in a row horizontally
			if (board[row][i] != player)
				break;
			count++;
		}

		if (count >= 4)
			return 1;

		count = 1;
		for (i = coll + 1, j = row + 1; i < size && j < size; ++i, ++j)
		{ // 4 in a row diagonally
			if (board[j][i] != player)
				break;
			count++;
		}
		for (i = coll - 1, j = row - 1; i >= 0 && j >= 0; --i, --j)
		{ // 4 in a row diagonally
			if (board[j][i] != player)
				break;
			count++;
		}

		if (count >= 4)
			return 1;

		count = 1;
		for (i = coll + 1, j = row - 1; i < size && j >= 0; ++i, --j)
		{ // 4 in a row diagonally
			if (board[j][i] != player)
				break;
			count++;
		}
		for (i = coll - 1, j = row + 1; i >= 0 && j < size; --i, ++j)
		{ // 4 in a row diagonally
			if (board[j][i] != player)
				break;
			count++;
		}
		if (count >= 4)
			return 1; // if the counter >=4 it means that there are 4 in a row
	}
	return 0;
}

void GameStart(int** Board, int size) // The function that starts the game and uses all the prevoius functions
{
	printf("\n\n****THE GAME IS STARTING****\n\n"); 

	int CollOf1, CollOf2, coll = 0, row ; // CollOf1 is the column that player 1 will choose, CollOf2 is the column that player 2 will choose
	int winner = 0, ForWin;
	while (winner == 0) // the function will repeat it self while there is no winner
	{
		if (TIE(Board, size) == TRUE) 
		{
			break; // leaves the loop of the while becuase there is no winner 
		}

		do // plays for player1 
		{
			printf("******PLAYER 1******\n");
			CollOf1 = GetNumber(coll, size);// gets the number from player1
			if (checkcol(Board, CollOf1, size, PLAYER1) == TRUE)
				break; // if true stop this loop and continue to the next functions
			else
				printf("This column is FULL, choose a new column!\n");

		} while (checkcol(Board, CollOf1, size, PLAYER1) != TRUE);

		row = GetRow(Board, CollOf1, size, PLAYER1); // gets the last row that the coin was putted in 
		ForWin = checkWin(Board, CollOf1, row, PLAYER1, size); // checks if the last coin that was putted is the coin that will make the win

		if (ForWin == 1) // if the coin was the winning one change the winner and leave the loop 
		{
			winner = 1;
			break;
		}

		PrintBoard(Board, size, size);// prints the board

		if (TIE(Board, size) == TRUE)
		{
			break; // leaves the loop of the while becuase there is no winner 
		}

		do // loop for player2 
		{
			printf("\n******PLAYER 2******\n");
			CollOf2 = GetNumber(coll, size);// gets the number from player2
			if (checkcol(Board, CollOf2, size, PLAYER2) == TRUE)
				break;// if true stop this loop and continue to the next functions
			else
				printf("This column is FULL, choose a new column!\n");

		} while (checkcol(Board, CollOf2, size, PLAYER2) != TRUE);

		row = GetRow(Board, CollOf2, size, PLAYER2);// gets the last row that the coin was putted in
		ForWin = checkWin(Board, CollOf2, row, PLAYER2, size);// checks if the last coin that was putted is the coin that will make the win

		if (ForWin == 1)// if the coin was the winning one change the winner and leave the loop
		{
			winner = 2;
			break;
		}

		PrintBoard(Board, size, size);
	} //while ended

	printf("________________________________________________________________\n");
	PrintBoard(Board, size, size);
	if (winner == 0) // if there was a tie 
		printf("\n***** The game ended in a TIE *****\n\n");
	if (winner == 1) // if player 1 wins
		printf("\nTHE WINNER IS PLAYER 1!!!\n");
	if (winner == 2) // if player 2 wins
		printf("\nTHE WINNER IS PLAYER 2!!!\n");

	printf("**** THE GAME IS OVER ****\n\n");

}

void FreeBoard(int*** Board, int size) // function to free the board
{
	int i;
	for (i = 0; i < size; ++i)
		free((*Board)[i]);

	free(*Board);
}