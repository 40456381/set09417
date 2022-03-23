#include <stdio.h>
#include "sudoku.h"

Sudoku * introduceGame()
{
	Sudoku * sudoku;
	printf("\nHELLLO AGAIN");
	int selection;
	printf("\nWELCOME TO CLARK'S SUDUKO GAME - MADE IN C\n"
		   "-------------------------------------------------\n"
		   "Please select from the following options\n"
		   "-------------------------------------------------\n"
		   "1) EASY\n"
		   "2) MEDIUM\n"
		   "3) HARD\n"
		   "4) Quit Program\n"
		   "Option: \n");
		   
	scanf("%d", &selection);
	
	switch(selection)
	{
		case 1:
		printf("playing EASY");
		
		break;
		
		case 2:
		printf("\nplaying MEDIUM\n");
		//select the MEDIUM BOARD
		
		//int ** puzzle;
		//int progress;
		Sudoku * sudoku;
		int shots = 0;

		//puzzle = createPuzzle();

		//sudoku = setUpPuzzle(puzzle);

		//printPuzzle(sudoku->squares);
		
		
					
		/*
		int row = 0;
		int col = 0;
		int numberChoice = 0;
		char correct = 'N';
		printf("please select a row that you would like to alter: ");
		scanf("%d", &row);
		while (correct == 'N')
		{	
			if (row < 1 ||  row > 9)
			{	printf("***************************************\n");
				printf("* row entered must be between 1 and 9 *\n");
				printf("***************************************\n");
				printf("please select a row that you would like to alter: ");
				scanf("%d", &row);
			}
			else 
			{
				correct = 'Y';
			}
		}
		//set correct back to N for next check
		correct = 'N';
		printf("row selection is %i \n", row);
		printf("please select a column that you would like to alter:  ");
		printf("\n");
		scanf("%d", &col);
		while (correct == 'N')
		{	
			if (col < 1 ||  col > 9)
			{	printf("***************************************\n");
				printf("* col entered must be between 1 and 9 *\n");
				printf("***************************************\n");
				printf("please select a col that you would like to alter: ");
				scanf("%d", &col);
			}
			else 
			{
				correct = 'Y';
			}
		}
		//set correct back to N for next check
		correct = 'N';
		printf("column selection is %i", col);
		printf("\n");
		printf("please enter the number that you would like to place in this position:  ");
		scanf("%d", &numberChoice);
		printf("\n");
		
		while (correct == 'N')
		{	
			if (numberChoice < 1 ||  numberChoice > 9)
			{	printf("******************************************\n");
				printf("* number entered must be between 1 and 9 *\n");
				printf("******************************************\n");
				printf("please enter the number that you would like to place in this position:  ");
				scanf("%d", &numberChoice);
			}
			else 
			{
				correct = 'Y';
			}
		}
		printf("the number you want to place on the board at row %i , column %i is ----> %i ", row, col, numberChoice);
		//create a function to take in row, col and number and then compare again the completed puzzle
		*/
		break;
		
		case 3:
		printf("playing HARD");
		break;
		
		case 4:
		printf("game has ended");
		exit(0);
		break;
	}
	return sudoku;
}