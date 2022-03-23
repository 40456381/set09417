/*
 * Clark Bolan 40456381 Connect 4 C Program
 * SET09417 Algorithms & Data Structures
 */
 
#include <stdio.h>
#include "sudoku.h"
#include <stdlib.h>

int UNSOLVED = 81;
int SIZE_ROWS = 9;
int SIZE_COLUMNS = 9;

int main()
{
	int ** puzzle;
	//int progress;
	Sudoku * sudoku;
	//int shots = 0;

	puzzle = createPuzzle();

	sudoku = setUpPuzzle(puzzle);

	printPuzzle(sudoku->squares);

	//UserSelection userSelection;
	struct UserSelection userpicks;
		
	sudoku = introduceGame();
	//while (UNSOLVED > 0)
	//{

		 userpicks = makeSelection();
		 //printf( "userSelection  row : %d\n", userpicks.row);
		 //try to update the puzzle checking the userpicks is valid
		 updateSudoku2(puzzle, userpicks);
		 //printPuzzle(sudoku->squares);
		
	//}
	
/*
    puzzle = createPuzzle();

    sudoku = setUpPuzzle(puzzle);

    printPuzzle(sudoku->squares);

	while (UNSOLVED > 0)
	{
		printf("\n");
		printf("this is shot %d\n", shots);
		progress = checkPuzzle(sudoku->squares, sudoku->boxes);
		printPuzzle(sudoku->squares);
		shots++;
		if (progress == 0)
		{	
			printf("failed to solve the puzzle");
			break;
		}
	}
	

    printf("\n");
	printf("\n");

    //printPuzzle(sudoku->squares);
	if (UNSOLVED == 0)
	{
		printf("\n");
		printf("WINNER");
	}
*/

    return 0;
}