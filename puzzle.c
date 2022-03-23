#include <stdio.h>
#include <stdlib.h>
#include "sudoku.h"

Sudoku * createSudoku(Square *** squares, Box ** boxes)
{
	Sudoku * sudoku;
	sudoku = malloc(sizeof(Sudoku));
	
	sudoku->squares = squares;
	sudoku->boxes = boxes;
	
	return sudoku;
}

Sudoku * setUpPuzzle(int ** puzzle)
{
    Square *** sudoku;
    Box ** boxes;
    int i, j, x;
    int currentBox = 0;

    sudoku = (Square***)malloc(sizeof(Square**)*9);
    boxes = createBoxes();

    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++)
    {
        /* malloc space for each row */
        sudoku[i] = (Square**)malloc(sizeof(Square*)*9);

        /* loop through columns */
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            /* malloc space for each square */
            sudoku[i][j] = (Square*)malloc(sizeof(Square)*9);

            /* assign number to sudoku  */
            sudoku[i][j]->number = puzzle[i][j];

            /* assign row and column numbers to each square */
            sudoku[i][j]->row = i;
            sudoku[i][j]->column = j;
            sudoku[i][j]->solvable = 9;

            boxes[currentBox]->squares[ boxes[currentBox]->numbers ] = sudoku[i][j];
            sudoku[i][j]->box = boxes[currentBox];
            boxes[currentBox]->numbers++;

            for (x = 0; x < SIZE_ROWS; x++)
            {
                sudoku[i][j]->possible[x] = 0;
            }

            if (j == 2)
                currentBox++;
            if (j == 5)
                currentBox++;

        }

        currentBox -= 2;
        if (i == 2)
            currentBox = 3;
        if (i == 5)
            currentBox = 6;
    }

    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++)
    {
        /* loop through columns */
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->number != 0)
            {
                sudoku[i][j]->solvable = 0;
                updateSudoku(sudoku, i, j);
                updateBoxes(sudoku, i, j);
                UNSOLVED--;
            }
        }
    }

    return createSudoku(sudoku, boxes);

}

int updateSudoku(Square *** sudoku, int row, int column)
{
    int x;
    int number = sudoku[row][column]->number;

    for (x = 0; x < SIZE_ROWS; x++)
    {
        if (sudoku[x][column]->possible[number - 1] == 0)
        {
            sudoku[x][column]->solvable--;
        }
        sudoku[x][column]->possible[number -1] = 1;
    }

    for (x = 0; x < SIZE_COLUMNS; x++)
    {
		
        if (sudoku[row][x]->possible[number - 1] == 0)
        {
            sudoku[row][x]->solvable--;
        }
        sudoku[row][x]->possible[number -1] = 1;
    }

    return 1;

}

UserSelection makeSelection()
{
		struct UserSelection userpicks;
		
		//int row = 0;
		//int col = 0;
		//int numberChoice = 0;
		int correct = 0;
		printf("please select a row that you would like to alter: ");
		scanf("%d", &userpicks.row);
		while (correct == 0)
		{	
			if (userpicks.row < 1 ||  userpicks.row > 9)
			{	printf("***************************************\n");
				printf("* row entered must be between 1 and 9 *\n");
				printf("***************************************\n");
				printf("please select a row that you would like to alter: ");
				scanf("%d", &userpicks.row);
			}
			else 
			{
				correct++;
				//scanf("%d", &userpicks.row);
			}
		}
		
		//set correct back to N for next check
		correct = 0;
		//printf("row selection is %d \n", userpicks.row);
		printf("please select a column that you would like to alter:  ");
		scanf("%d", &userpicks.col);
		//printf(" col entered is %i \n", col);
		while (correct == 0)
		{	
			if (userpicks.col < 1 ||  userpicks.col > 9)
			{	printf("***************************************\n");
				printf("* col entered must be between 1 and 9 *\n");
				printf("***************************************\n");
				printf("please select a col that you would like to alter: ");
				scanf("%d", &userpicks.col);
			}
			else 
			{
				correct++;
				//scanf("%d", &userpicks.col);
			}
		}
		//set correct back to N for next check
		correct = 0;
		//printf("column selection is %d", userpicks.col);
		printf("\n");
		printf("please enter the number that you would like to place in this position:  ");
		scanf("%d", &userpicks.numberChoice);
		printf("\n");
		
		while (correct == 0)
		{	
			if (userpicks.numberChoice < 1 ||  userpicks.numberChoice > 9)
			{	printf("******************************************\n");
				printf("* number entered must be between 1 and 9 *\n");
				printf("******************************************\n");
				printf("please enter the number that you would like to place in this position:  ");
				scanf("%d", &userpicks.numberChoice);
			}
			else 
			{
				correct++;
				//scanf("%d", &userpicks.numberChoice);
				
			}
		}
		printf("the number you want to place on the board at row %d , column %d is ----> %d ", userpicks.row, userpicks.col, userpicks.numberChoice);
		
		printf("\n");

	return userpicks;
}

int updateSudoku2(Square *** puzzle, UserSelection userpicks)
{
			printf("what is userpicks.numberChoice %d \n", userpicks.numberChoice);
			printf("what is userpicks.row  %d \n", userpicks.row);
			printf("what is userpicks.col  %d \n", userpicks.col);   
			int x, y;
			int i, j;
			userpicks.row--;
			userpicks.col--;
			/* loop through rows */
			for (i = 0; i < SIZE_ROWS; i++)
				
				{
					printf("what row in the loop %i \n", i);
					
					/* loop through columns */
					for (j = 0; j < SIZE_COLUMNS; j++)
					{
						printf("what column in the loop %i \n", j);
						
						//printf("%d\n", puzzle[i][j]);
						x = puzzle[i][j];
						y = userpicks.numberChoice;
						printf("what is x %d\n", x);
						if((i == userpicks.row && j == userpicks.col) && (x == y))
							
						{
							printf("The selection you have made is already holding your number\n");
							//TODO need to ask again
							//exit(0);
						}
						else if (x == 0) //the position is empty so we can update the array
						{
							printf("updateing the array\n");
							puzzle[userpicks.row][userpicks.col] = userpicks.numberChoice;
							printPuzzle(puzzle);
							exit(0);
						}
						//printf("\t%d" , puzzle[i][j]);
						

					}
					printf("\n");
				}

    return 1;
}	

int checkPuzzle(Square *** sudoku, Box ** boxes)
{
    int i, j, x;

    /* loop through rows */
    for (i = 0; i < SIZE_ROWS; i++)
    {
        /* loop through columns */
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            if (sudoku[i][j]->solvable == 1)
            {
                solveSquare(sudoku[i][j]);
                updateSudoku(sudoku, i, j);
				updateBoxes(sudoku, i ,j); 
				
				return 1;
            }

        }

    }
	
	if (boxSingles(sudoku, boxes))
	{
		return 1;
	}
	
	return checkRows(sudoku, boxes);
    
}

int ** createPuzzle()
{
    int ** puzzle;
    int i, j;
    int array[9][9]= {0, 1, 9,      0, 0, 2,     0, 0, 0,
                      4, 7, 0,      6, 9, 0,     0, 0, 1,
                      0, 0, 0,      4, 0, 0,     0, 9, 0,

                      8, 9, 4,      5, 0, 7,     0, 0, 0,
                      0, 0, 0,      0, 0, 0,     0, 0, 0,
                      0, 0, 0,      2, 0, 1,     9, 5, 8,

                      0, 5, 0,      0, 0, 6,     0, 0, 0,
                      6, 0, 0,      0, 2, 8,     0, 7, 9,
                      0, 0, 0,      1, 0, 0,     8, 6, 0 };

    puzzle = (int**)malloc(sizeof(int*)*9);

    for (i = 0; i < 9; i++)
    {
        puzzle[i] = (int*)malloc(sizeof(int)*9);

        for (j = 0; j < 9; j++)
        {
            puzzle[i][j] = array[i][j];
        }
    }

    return puzzle;
}

void printPuzzle(Square *** puzzle)
{
    int i, j;

    printf("-------------------------------\n");
    for (i = 0; i < SIZE_ROWS; i++)
    {
        printf("|");
        /* print each row */
        for (j = 0; j < SIZE_COLUMNS; j++)
        {
            printf(" %d ", puzzle[i][j]->number);

            if (((j + 1) % 3) == 0)
            {
                printf("|");
            }
        }
        printf("\n");
        if (((i + 1) % 3) == 0)
        {
            printf("-------------------------------\n");
        }
    }
}