#include <stdio.h>
#include <stdlib.h>
const short int HEIGHT=3,WIDTH=3, AMT_TO_WIN = 3; //some constant, i tried to make the code expandable/ easy to change
typedef enum sym{
	BLANK,
	CIRCLE,
	CROSS = -1
}sym; //here i use enum to make "X" as -1 and "O" as 1, making the win calculation can be done by simple addition


void fieldInit(sym field[WIDTH][HEIGHT]){
	for(int i=0;i<=HEIGHT-1;i++)
		for(int j=0;j<=WIDTH-1;j++)
			field[j][i]=BLANK;
}

char symPrint(sym a) //convert enum to char
{
	switch (a)
	{
	case 0:
		return '-';
		break;
	case 1:
		return 'O';
		break;
	case -1:
		return 'X';
		break;
	default:
		break;
	}
	return 0;
}

void printField(sym field[WIDTH][HEIGHT]){ //prints current field with some formatting
	for(int i=0;i<=HEIGHT-1;i++){
		int j=0;
		for(j=0;j<=WIDTH*4;j++)
			printf("-");
		printf("\n");
		for(j=0;j<=WIDTH-1;j++)
			printf("| %c ",symPrint(field[j][i]));
		printf("|\n");
	}
	
}

int winCheck(sym field[WIDTH][HEIGHT])
{	
	int sum=0;
	for(int i=0;i<=HEIGHT-1;i++){ //horizontal check
		for(int j=0;j<WIDTH-1;j++){
			sum+=field[j][i];
		}
		//printf("H-check sum #%i : %i\n",i,sum); //debug
		if(abs(sum)==3){ //most of the case will be false so there will be no furthur check thus faster code run
			return sum<0?-1:1; //
		}else{
			sum=0;
		}
	}
	for(int i=0;i<WIDTH-1;i++){//vertical check, somehow i wanna cater for cases of non-square field so i decide not to make it a child function
		for(int j=0;j<=HEIGHT-1;j++){
			sum+=field[i][j];
		}
		//printf("V-check sum #%i : %i\n",i,sum); //debug
		if(abs(sum)==3){ 
			return sum<0?-1:1; 
		}else{
			sum=0;
		}
	}

		sum=0;
		for(int i=0;i<=WIDTH-1;i++){ //diagonal check, down slope
			sum+=field[i][i];
		}

		//printf("d-check sum #0 : %i\n",sum); //debug

		if(abs(sum)==3){ 
			return sum<0?-1:1; 
		}else{
			sum=0;
		}

		for(int i=0;i<=WIDTH-1;i++){ //diagonal check, up slope
			sum+=field[i][HEIGHT-i-1];
		}

		//printf("d-check sum #1 : %i\n",sum); //debug

		if(abs(sum)==3){ 
			return sum<0?-1:1; 
		}else{
			sum=0;
		}
		
	return 0;
}

void callTurn(int turn,sym field[WIDTH][HEIGHT])
{
	int x,y;
	if (!turn)
	{
		printf("Welcome to the tic tac toe! X's turn\n");
		return;
	}
	printf("Turn %i (%c), type in x and y location (zero-based, of course)", turn, turn % 2 ? symPrint(CIRCLE) : symPrint(CROSS));
	scanf("%d%d",&x,&y);
	if(field[x][y]==BLANK){
		field[x][y]=turn % 2 ? CIRCLE : CROSS;
	}else{
		printf("You changing existing mark is not allowed! choose again\n");
		callTurn(turn,field);
	}
	return;
}

int main()
{
	int turn = 0; 
	int win = 0;
	sym field[WIDTH][HEIGHT];
	fieldInit(field);
	printf("playfield initialized:\n");
	//printField(field);
	while (!win)
	{
		callTurn(turn,field);
		printf("current playfield:\n");
		printField(field);
		win = winCheck(field);
		turn++;
	}
	printf("\"%c\" has won!\n", win==1 ? symPrint(CIRCLE) : symPrint(CROSS));
	return 0;
}