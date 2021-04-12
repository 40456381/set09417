/*
 * Clark Bolan 40456381 Connect 4 C Program
 * SET09417 Algorithms & Data Structures
 * Happy Playing
 */

#include <stdio.h>
#include <windows.h>

//declared constants
#define TRAD_ROWS 6
#define TRAD_COLS 7
#define TRAD_BOARD_TOTAL 42

/* Function declarations */
void introduceGame(struct stack *s, int whosShot, int gameType);
void createBoard(struct stack *s);
void renderBoard(struct stack *s);
void play(struct stack *s, int whosShot, int gameOver);
void takeTurns(struct stack *s, int whosShot, int row, int col, int gameOver);
void init_stack(struct stack *s);
void push(struct stack *s, int item);
void *pop(struct stack *s);
int dropCounter(struct stack *s, int whosShot, int row, int col, int slot, int gameOver, char playerPiece[2], int gameType);
//void undoShot(struct stack *s, char undo, int whosShot, int slot, int iRow);
//void redoShot(struct stack *s, char redo, int whosShot, int slot, char playerPiece[2], int iRow);
int checkforWin(struct stack *s, int row, int col, char playerPiece[2], int gameOver, int whosShot);


//gameOver and gameType variables initialised in global scope to allow the program to stop when game is won
int gameOver  = 0;
int gameType  = 0;

//declaring struct for type stack
struct stack
{
    char** board;
    int array[70];
    int top;
};

//Main funtion and entry point to the application
int main (int argc, char *argv[])
{
	struct stack s;
	int whosShot = 0;
	init_stack(&s);
	
	introduceGame(&s, whosShot, gameType);
	
}

/*creates splash screen with game options, after user selects
option switch is invoked and program branches of to that game mode*/
void introduceGame(struct stack *s, int whosShot, int gameType)
{
	int selection;
	printf("\nWELCOME TO CLARK'S CONNECT 4 GAME - MADE IN C\n"
		   "-------------------------------------------------\n"
		   "Please select from the following options\n"
		   "-------------------------------------------------\n"
		   "1) Traditional game board\n"
		   "2) Traditional game with undo and redo features\n"
		   "3) Reload Last Game\n"
		   "4) Quit Program\n"
		   "Option: \n");
		   
	scanf("%d", &selection);
	
	switch(selection)
	{
		case 1:
		//printf("playing selection1");
		gameType = 1;
		createBoard(s);
		renderBoard(s);
		play(s, whosShot, gameOver);
		break;
		
		case 2:
		gameType = 2;
		printf("playing selection2");
		createBoard(s);
		renderBoard(s);
		play(s, whosShot, gameOver);
		break;
		
		case 3:
		printf("playing selection3");
		break;
		
		case 4:
		printf("game has ended");
		exit(0);
		break;
	}
}

//starts the game play
void play(struct stack *s, int whosShot, int gameOver)
{
	while(gameOver == 0)
	{
		int row = TRAD_ROWS;
		int col = TRAD_COLS;	
		takeTurns(s, whosShot, row, col, gameOver);
		//checkForWin();	
	}
	//sort out the winner
	if(whosShot == 0){
		whosShot = 1;
	}
	else{
		whosShot = 2;
	}
	printf("\nTHE WINNER IS PLAYER %d \n", whosShot);
	//reset whosShot
	whosShot = 0;
	introduceGame(s, whosShot, gameType);
		
}

//Method that loops round until game is won
void takeTurns(struct stack *s, int whosShot, int row, int col, int gameOver)
{
	int slot = 0;
	char playerPiece[2] = {'O','X'};
	
	//ask for input until valid
	do{
		char validSlot = 'Y';
		if(whosShot == 0)
		{
			printf("\n");
			printf("\nPlayer 1, please enter a column you would like your 'O' counter to drop, enter a selection between 1 and 7\n");
		}
		else
		{
			printf("\n");
			printf("\nPlayer 2, please enter a column you would like your 'X' counter to drop, enter a selection between 1 and 7\n");
		}
		
		scanf("%i", &slot);
		
		//check for correct selection
		if (slot < 1 || slot > 7)
		{
			printf("\nIncorrect slot selection please enter between 1 and 7\n");
			Sleep(2000);
			validSlot = 'N';
		}
			if (validSlot == 'Y'){
			push(s, slot);
			dropCounter(s, whosShot, row, col, slot, gameOver, playerPiece, gameType);
			}
			
	}while(gameOver == 0);	
	
 
}


int dropCounter(struct stack *s, int whosShot, int row, int col, int slot, int gameOver, char playerPiece[2], int gameType)
{
	char undo = 'N';
	char redo = 'N';
	int iRow;
		if (gameOver == 0){
		//this takes away 1 to deal with arrays starting at 0
			slot --;
			
			for (int i = row - 1; i < row; i--)
			{
				iRow = i;
				//checking for free area on board
				if(s->board[i][slot] == ' ')
				{
					//Comment this
					//printf("\nWHAT IS PLAYERPIECE %c\n", playerPiece[whosShot]);
					//printf("\nWHAT IS whosShot %d\n", whosShot);
					//printf("\nWHAT IS slot %d\n", slot);
					s->board[i][slot] = playerPiece[whosShot];
					//TODO check if won
					gameOver = checkforWin(s, row, col, playerPiece, gameOver, whosShot);
					if (gameOver == 1){
						renderBoard(s);
						//get back to the play() method
						play(s, whosShot, gameOver);
						//terminate the loop
						break;
					}
					
					//moves to next player
					if (whosShot == 0){
						whosShot = 1;
					}
					else{
						whosShot = 0;
					}
					renderBoard(s);
					
					//these methods are for undo redo feature game
					//if (gameType == 2){
					//	undoShot(s, undo, whosShot, slot, iRow);
					//	redoShot(s, redo, whosShot, slot, playerPiece, iRow);
					//}
					play(s, whosShot, gameOver);
				}
				//checking if column is full
				else if(i == 0 && s->board[i][slot] != ' ')
				{
					printf("\nposition is taken\n");
					takeTurns(s, whosShot, row, col, gameOver);
				}
		}
	}

	return gameOver;
}


int checkforWin(struct stack *s, int row, int col, char playerPiece[2], int gameOver, int whosShot)
{
	//Vertical Check
    for(int i = 0; i < row-3; i++)
        for(int j = 0; j < col; j++)
            if(s->board[i][j] != ' ' && s->board[i][j] == playerPiece[whosShot] && s->board[i][j] == s->board[i+1][j]
                && s->board[i][j] == s->board[i+2][j] && s->board[i][j] == s->board[i+3][j])
            {
                gameOver = 1;
                return gameOver;
            }
    //Horizontal check
    for(int i = 0; i < row; i++)
        for(int j = 0; j < col-3; j++)
            if(s->board[i][j] != ' ' && s->board[i][j] == playerPiece[whosShot] && s->board[i][j] == s->board[i][j+1]
                && s->board[i][j] == s->board[i][j+2] && s->board[i][j] == s->board[i][j+3])
            {
                gameOver = 1;
                return gameOver;
            }
    //Positive diagonal check
    for(int i=0; i < row-3; i++)
        for(int j = 0; j < col-3; j++)
            if(s->board[i][j] != ' ' && s->board[i][j] == playerPiece[whosShot] && s->board[i][j] == s->board[i+1][j+1] 
                && s->board[i][j] == s->board[i+2][j+2] && s->board[i][j] == s->board[i+3][j+3])
            {
                gameOver = 1;
                return gameOver;
            }
    //negative diagonal check   
    for(int i=3; i < row; i++)
        for(int j = 0; j < col-3; j++)
            if(s->board[i][j] != ' ' && s->board[i][j] == playerPiece[whosShot] && s->board[i][j] == s->board[i-1][j+1]   
                && s->board[i][j] == s->board[i-2][j+2] && s->board[i][j] == s->board[i-3][j+3])
            {
                gameOver = 1;
                return gameOver;
            }
    return gameOver;
}





//creates the game board using the constant values declared at top of program
void createBoard(struct stack *s)
{
	//allocates required memory for the game board
    s->board = (char **)malloc(TRAD_ROWS*sizeof(char *));
    
    for(int i = 0; i < TRAD_ROWS; i++)
        s->board[i] = (char *)malloc(TRAD_COLS*sizeof(char *));
    
    for(int i = 0; i < TRAD_ROWS; i++)
        for(int j = 0; j < TRAD_COLS; j++)
            s->board[i][j] = ' ';
}

//renders the game board to the screen
void renderBoard(struct stack *s)
{
	FILE * finout; //finout is a file pointer
	finout = fopen("savedGame.txt", "a"); //create game recording file	
    //system("cls");
    printf("\n");
	fprintf(finout,"\n");
    for(int y = 0; y < TRAD_ROWS; y++)
    {
        for(int x = 0; x < TRAD_COLS; x++)
        {
            printf("----");
			fprintf(finout, "----");
		
        }
        printf("-\n"
               "|");
		fprintf(finout, "-\n"
               "|");	   
              
        for(int x = 0; x < TRAD_COLS; x++)
        {
            printf(" %c |", s->board[y][x]);
			fprintf(finout, " %c |", s->board[y][x]);
        }
        printf("\n");
		fprintf(finout,"\n");
    }
    
    for(int x = 0; x < TRAD_COLS; x++)
        {
            printf("----");
			fprintf(finout,"----");
        }
        printf("-\n");
		fprintf(finout,"-\n");
    
    for(int x = 0; x < TRAD_COLS; x++)
        {
            printf("  %x ", x+1);
			fprintf(finout, "  %x ", x+1);
        }
		
	
	fclose(finout);	
}

//undo function
/*
void undoShot(struct stack *s, char undo, int whosShot, int slot, int iRow)
{	
	//ask player if they want to undo
	printf("\nwould you like to undo that move, player %d? (Y/N)\n", whosShot);
	getchar();
	scanf("%c", &undo);
	if (undo == 'Y')
	{
		printf("\nWHAT IS undo %c\n", undo);
		pop(s);
		s->board[iRow][slot] = ' ';
		printf("\nplayer %d has decided to undo last shot\n", whosShot);
		renderBoard(s);
	}
}
*/

//redo function
/*
void redoShot(struct stack *s, char redo, int whosShot, int slot, char playerPiece[2], int iRow)
{	
	whosShot --;
	//ask player if they want to redo
	printf("\nwould you like to redo that move, player %d? (Y/N)\n", whosShot);
	getchar();
	scanf("%c", &redo);
	if (redo == 'Y')
	{
		printf("\nWHAT IS redo %c\n", redo);
		push(s, slot);
		s->board[iRow][slot] = playerPiece[whosShot];
		printf("\nplayer %d has decided to redo last shot\n", whosShot);
		renderBoard(s);
	}
}
*/

/*initialise the stack
we set the value to the top of the stack to -1 to indicate that
it is empty*/
void init_stack(struct stack *s)
{
    s->top = -1;
}
/*push onto the top of the stack
we are just putting new things
*/
void push(struct stack *s, int item)
{
    if(s->top == TRAD_BOARD_TOTAL-1)
    {
        printf("Stack is full.");
        return;
    }
    s->top++;
    s->array[s->top] = item;
}
/*pop off the stack
create temp storage for item coming off atack
check if stack is empty and issue message "Stack is emtpy"
*/
void *pop(struct stack *s)
{
    int *data;
    if(s->top == -1)
    {
        printf("Stack is empty\n");
        return NULL;
    }
    data = &s-> array[s->top];
    s->top--;
    return data;
}