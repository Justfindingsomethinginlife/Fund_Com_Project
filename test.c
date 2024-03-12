#include<stdio.h>
#include<conio.h>
#include<windows.h>

void gotoxy( int column, int line )
{
	  COORD coord;
	    coord.X = column;
	      coord.Y = line;
	        SetConsoleCursorPosition(
				    GetStdHandle( STD_OUTPUT_HANDLE ),
				        coord
					    );
}

void update_screen(char screen[][30],int player_x, int player_y, char playerchar);
int move(char screen[][30],int *player_x,int *player_y, char *playerchar,int *score);
void Welcome();
void help_screen();
void Menu(int option);

int main()
{
	char area[30][30];char modesel;
	int player_x,player_y;int option=0;
	player_x=3;player_y=3;
	char playerchar = '^';
	
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(i==0 || i==29 || j==0 || j==29)area[i][j]='#';
			else area[i][j] = ' '; 
		}
	}
	//WELCOME!
	Welcome();
	
	//PLEASE MAKE A DECISION
	while(1)
	{	
		if(modesel == 13)break; 
		if(modesel == 'W' || modesel == 'w')option++;
		else if(option>0 && (modesel == 'S' || modesel == 's'))option--;
		else if(option == 0 && (modesel == 'S' || modesel == 's'))option == 1;
		option %= 2;
		Menu(option);
		modesel = getch();
	}

		// obstacle R stand for Rocks
	area[1][1]   = 'R';
	area[1][2]   = 'R';
	area[1][3]   = 'R';
	area[1][4]   = 'R';
	area[1][5]   = 'R';
	area[2][1]   = 'R';
	area[2][2]   = 'R';
	area[2][3]   = 'R';
	area[3][4]   = 'R';
	area[3][2]   = 'R';
	area[13][9]  = 'R';
	area[13][10] = 'R';
	area[13][11] = 'R';
	area[13][12] = 'R';
	area[15][13] = 'R';
	area[13][14] = 'R';
	area[13][15] = 'R';
	area[12][12] = 'R';
	area[12][13] = 'R';
	area[15][14] = 'R';
	area[26][1]  = 'R';
	area[26][2]  = 'R';
	area[26][3]  = 'R';
	area[26][4]  = 'R';
	area[26][7]  = 'R';
	area[26][8]  = 'R';
	area[26][9]  = 'R';
	area[7][18]  = 'R';
	area[6][19]  = 'R';
	area[6][20]  = 'R';

	// W stand for Woods
	area[13][1]  = 'W';
	area[12][2]  = 'W';
	area[11][3]  = 'W';
	area[10][4]  = 'W';
	area[27][9]  = 'W';
	area[27][10] = 'W';
	area[28][9]  = 'W';
	area[28][10] = 'W';
	area[28][11] = 'W';
	area[21][22] = 'W';
	area[21][23] = 'W';
	area[22][21] = 'W';
	area[22][22] = 'W';
	area[22][23] = 'W';
	area[22][24] = 'W';
	area[23][22] = 'W';
	area[23][23] = 'W';

	system("cls");
	int score=0;
	while(1)
	{
		update_screen(area,player_x,player_y,playerchar);
		if(move(area,&player_x,&player_y,&playerchar,&score) == 0)
		{printf("%d\n",score);return 0;}
		printf("%c ",playerchar);
		//if(area[player_y][player_x] == 'R' || area[player_y][player_x] == 'W')score++;
		gotoxy(0,0);
	}
	

}

int move(char screen[][30],int *player_x,int *player_y,char *playerchar, int *score)
{	
	char Direction;
	Direction = getch();
	switch(Direction)
	{
		case 'w':
			if((*player_y) == 1)break;
			(*player_y)--;
			(*playerchar) = '^';
			break;
		case 'd':
			if((*player_x) == 28)break;
			(*player_x)++;
			(*playerchar) = '>';
			break;
		case 's':
			if((*player_y) == 28)break;
			(*player_y)++;
			(*playerchar) = '^';
			break;
		case 'a':
			if((*player_x) == 1)break;
			(*player_x)--;
			(*playerchar) = '<';
			break;
		case 'e':
			switch(screen[*player_y][*player_x])
			{
				case 'W':
					(*score)++;
					screen[*player_y][*player_x] = ' ';
					break;
				case 'R':
					(*score)++;
					screen[*player_y][*player_x] = ' ';
					break;
			}
			break;
		case 27:
			return 0;
	}
	return 1;

}


void update_screen(char screen[][30],int player_x, int player_y, char playerchar)
{
	for(int i=0;i<30;i++)
	{	
		char line[61];
		line[60] = '\0';
		for(int j=0;j<30;j++)
		{
			if(j == player_x && i == player_y) line[2*j]=playerchar;
			else line[2*j] = screen[i][j];
		}
		for(int j=1;j<60;j=j+2)line[j] = ' ';
		puts(line);
	}
}

void help_screen()
{
	printf("WORK IN PROGRESS");
}

void Menu(int option)
{	
	FILE *fp;
	int b[3];
	fp = fopen("Menu.bin","rb");
		for(int i=0;i<30;i++)
		{
			for(int j=0;j<30;j++)
			{
				fread(b,1,1,fp);printf("%c ",b[0]);
				switch(option)
				{
					case 0:
						if( i*30+j == 221){
							printf("\x1b[2D");
							printf(">");
							printf("\x1b[1C");
							printf("\e[91m");
						}
						if( i*30+j == 227)
						{
							printf("\e[0m");
						}
						break;
					case 1:
						if( i*30+j == 281){
							printf("\x1b[2D");
							printf(">");
							printf("\x1b[1C");
							printf("\e[91m");
						}
						if( i*30+j == 286)
						{
							printf("\e[0m");
						}
						break;

				}
				
			}
			printf("\n");
		}
		fseek(fp,0,SEEK_SET);
}

void menu_disp()
{
	
}




void Welcome()
{
	char Welcome[30][30];
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(i==0||i==29||j==0||j==29)Welcome[i][j]='#';
			else Welcome[i][j] = ' ';
		}
	}
	Welcome[13][12] ='W';
	Welcome[13][13] = 'e';
	Welcome[13][14] = 'l';
	Welcome[13][15] = 'c';
	Welcome[13][16] = 'o';
	Welcome[13][17] = 'm';
	Welcome[13][18] = 'e';

	Welcome[15][9] = 'P';
	Welcome[15][10] = 'r';
	Welcome[15][11] = 'e';
	Welcome[15][12] = 's';
	Welcome[15][13] = 's';
	Welcome[15][14] = ' ';
	Welcome[15][15] = 'A';	
	Welcome[15][16] = 'n';
	Welcome[15][17] = 'y';
	Welcome[15][18] = ' ';
	Welcome[15][19] = 'K';
	Welcome[15][20] = 'e';
	Welcome[15][21] = 'y';
	
	
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)printf("%c ",Welcome[i][j]);
		printf("\n");
	}
	//printf("\e[46m P \e[40m \n");

	getch();	
}
