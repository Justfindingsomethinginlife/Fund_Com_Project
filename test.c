#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

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

typedef struct{
	int player_x;
	int player_y;
	char playerchar;
	int Nscore;
	int Wscore;
	int Rscore;
	int Ascore;
}Player;

void colorized(char screen[][30],int color[][30])
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(screen[i][j] == 'a' || screen[i][j] == 'e' || screen[i][j] == 'i' || screen[i][j] == 'm' || screen[i][j] == 'q' || screen[i][j] == 'u' || screen[i][j] == 'y' || screen[i][j] == 'C'){}
			else if (screen[i][j] == 'b' || screen[i][j] == 'f' || screen[i][j] == 'j' || screen[i][j] == 'n' || screen[i][j] == 'r' || screen[i][j] == 'v' || screen[i][j] == 'z' || screen[i][j] == 'D'){*(*(color+i)+j) = 32;}
			else if (screen[i][j] == 'c' || screen[i][j] == 'g' || screen[i][j] == 'k' || screen[i][j] == 'o' || screen[i][j] == 's' || screen[i][j] == 'w' || screen[i][j] == 'A'){*(*(color+i)+j) =33;}
			else if (screen[i][j] == 'd' || screen[i][j] == 'h' || screen[i][j] == 'l' || screen[i][j] == 'p' || screen[i][j] == 't' || screen[i][j] == 's' || screen[i][j] == 'B'){*(*(color+i)+j) = 31;}
			else *(*(color+i)+j)=39;
		}
	}
}

void randomize(char screen[][30])
{	
	srand(time(NULL));
	char normal[] = {'a','e','i','m','q','u','y','C'};
	char weird[] =  {'b','f','j','n','r','v','z','D'};
	char rare[] =   {'c','g','k','o','s','w','A'};
	char animal[] = {'d','h','l','p','t','s','B'};
	char temp[30][30];
	
	memcpy(temp,screen,sizeof temp);

	int i,j;
	int randi;
	int count=0;
	int price=0;
	while(count<5)
	{	
		i=1 + rand()%27;
		j=1 + rand()%27;
		int prob=rand()%100;
		if(prob <= 30 && prob >=0)
		{
			if((*(*(screen+i)+j)!= 'W' && *(*(screen+i)+j) != 'R'))
			{	
				randi = rand()%8;
				*(*(screen+i)+j) = normal[randi];
				count++;
				price+=7;
			}

		}
		else if(prob >= 31 && prob <= 60)
		{
			if((*(*(screen+i)+j)!= 'W' && *(*(screen+i)+j) != 'R'))
                        {
                                randi = rand()%8;
                                *(*(screen+i)+j) = weird[randi];
                                count++;
				price+=15;
                        }
			
		}
		else if(prob >= 61 && prob <=70)
		{
			if((*(*(screen+i)+j)!= 'W' && *(*(screen+i)+j) != 'R'))
                        {
                                randi = rand()%7;
                                *(*(screen+i)+j) = rare[randi];
                                count++;
				price+=30;
                        }

		}
		else if(prob >= 71 && prob <= 100)
		{
			if((*(*(screen+i)+j)!= 'W' && *(*(screen+i)+j) != 'R'))
                        {
                                randi = rand()%7;
                                *(*(screen+i)+j) = animal[randi];
                                count++;
				price+=10;
                        }

		}

		if(count == 5 && price < 100)
		{
			memcpy(screen,temp,sizeof temp);
			count = 0;
			price = 0;
		}
	}
}

void colored_screen(char screen[][30],int color[][30],Player* player1);
void update_screen(char screen[][30],int player_x, int player_y, char playerchar);
int move(char screen[][30],Player* player1);
void Welcome();
void help_screen();
void Pause();
void Menu(int option);
void EndScreen(int option,int money);

int main()
{
	Player player1 = {3,3,'^',0,0,0,0};
	char area[30][30];char modesel;int color[30][30];
	int option=0;



	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(i==0 || i==29 || j==0 || j==29)area[i][j]='#';
			else area[i][j] = ' '; 
		}
	}

start:
	printf("\x1b[?25l");
	//WELCOME!
	
	player1.player_x = 3;
	player1.player_y = 3;
	player1.Nscore = 0;
	player1.Wscore = 0;
	player1.Rscore = 0;
	player1.Ascore = 0;

	Welcome();
	system("cls");	
	//PLEASE MAKE A DECISION
	while(1)
	{	
		if(modesel == 13)
		{
			if(option == 1)
			{
				gotoxy(0,0);
				while(1)
				{
					help_screen();
					if(getch() == 27)break;
					gotoxy(0,0);
				}
			}
			if(option==0)break;
		}
		gotoxy(0,0);
		if(modesel == 'S' || modesel == 's')option++;
		else if(option>0 && (modesel == 'W' || modesel == 'w'))option--;
		else if(option == 0 && (modesel == 'W' || modesel == 'w'))option == 1;
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
	randomize(area);
	colorized(area,color);
	int score=0;int count=5;
	while(1)
	{
		//update_screen(area,player1.player_x,player1.player_y,player1.playerchar);
		if(count == 0)break;
		colored_screen(area,color,&player1);
		int flag = move(area,&player1);
		if(flag == 0)
		{	
			gotoxy(0,0);
			while(1)
			{
				Pause();
				char c;
				c = getch();
				if(c == 27)break;
				if(c == 104)
				{
					gotoxy(0,0);
                                	while(1)
                                	{
                                        	help_screen();
                                        	if(getch() == 27)break;
                                        	gotoxy(0,0);
                                	}
					gotoxy(0,0);
				}
				if(c == 'q')goto end;
				gotoxy(0,0);
			}

		}
		else if (flag == 2)
		{
			count--;
		}
		//printf("%c ",player1.playerchar);
		//if(area[player_y][player_x] == 'R' || area[player_y][player_x] == 'W')score++;
		gotoxy(0,0);
	}

end:
	system("cls");
	printf("Total Normal : %d\n-----------------\n",player1.Nscore);
	Sleep(1000);
	printf("Total \x1b[31mWeird\x1b[39m : %d\n-----------------\n",player1.Wscore);
	Sleep(1000);
	printf("Total \x1b[33mRare\x1b[39m : %d\n-----------------\n",player1.Rscore);
	Sleep(1000);
	printf("Total \x1b[32mAnimal\x1b[39m : %d\n-----------------\n",player1.Ascore);
	Sleep(1000);
	printf("\x1b[33mCash\x1b[39m : \x1b[33m%d\x1b[39m", 7*player1.Nscore + 15*player1.Wscore + 30*player1.Rscore + 10*player1.Ascore);
	printf("\x1b[?25h");

	Sleep(1000);

	modesel=0;
	while(1)
	{	
		printf("\x1b[?25l");
		if(modesel == 13 && option == 0)goto start;
		if(modesel == 13 && option == 1){system("cls");break;}
		if(modesel == 'D' || modesel == 'd')option++;
                else if(option>0 && (modesel == 'A' || modesel == 'a'))option--;
                else if(option == 0 && (modesel == 'A' || modesel == 'a'))option == 1;
                option %= 2;
		EndScreen(option,7*player1.Nscore + 15*player1.Wscore + 30*player1.Rscore + 10*player1.Ascore);
		modesel = getch();
	}
	

}

int move(char screen[][30],Player* player1)
{	
	 printf("%d %d %c %d %d %d %d\n",player1->player_x,player1->player_y,player1->playerchar,player1->Nscore,player1->Wscore,player1->Rscore,player1->Ascore);
        char Direction;
        Direction = getch();
        switch(Direction)
        {
                case 'w':
                        if((player1->player_y) == 1 || screen[(player1->player_y)-1][player1->player_x] == 'W' || screen[(player1->player_y)-1][player1->player_x] == 'R')break;
                        (player1->player_y)--;
                        (player1->playerchar) = '^';
                        break;
                case 'd':
                        if((player1->player_x) == 28 || screen[(player1->player_y)][player1->player_x + 1] == 'W' || screen[(player1->player_y)][player1->player_x + 1] == 'R')break;
                        (player1->player_x)++;
                        (player1->playerchar) = '>';
                        break;
                case 's':
                        if((player1->player_y) == 28 || screen[(player1->player_y)+1][player1->player_x] == 'W' || screen[(player1->player_y)+1][player1->player_x] == 'R')break;
                        (player1->player_y)++;
                        (player1->playerchar) = '^';
                        break;
                case 'a':
                        if((player1->player_x) == 1 || screen[(player1->player_y)][player1->player_x - 1] == 'W' || screen[(player1->player_y)][player1->player_x - 1] == 'R')break;
                        (player1->player_x)--;
                        (player1->playerchar) = '<';
                        break;
                case 'e':
			int i = player1->player_y;
			int j = player1->player_x;

				if(screen[i][j] == 'a' || screen[i][j] == 'e' || screen[i][j] == 'i' || screen[i][j] == 'm' || screen[i][j] == 'q' || screen[i][j] == 'u' || screen[i][j] == 'y' || screen[i][j] == 'C'){(player1->Nscore)++;*(*(screen+i)+j)=' ';return 2;}
				 else if (screen[i][j] == 'b' || screen[i][j] == 'f' || screen[i][j] == 'j' || screen[i][j] == 'n' || screen[i][j] == 'r' || screen[i][j] == 'v' || screen[i][j] == 'z' || screen[i][j] == 'D'){(player1->Wscore)++;*(*(screen+i)+j)=' ';return 2;}
				else if (screen[i][j] == 'c' || screen[i][j] == 'g' || screen[i][j] == 'k' || screen[i][j] == 'o' || screen[i][j] == 's' || screen[i][j] == 'w' || screen[i][j] == 'A'){(player1->Rscore)++;*(*(screen+i)+j)=' ';return 2;}
                        else if (screen[i][j] == 'd' || screen[i][j] == 'h' || screen[i][j] == 'l' || screen[i][j] == 'p' || screen[i][j] == 't' || screen[i][j] == 's' || screen[i][j] == 'B'){(player1->Ascore)++;*(*(screen+i)+j)=' ';return 2;}
                        break;
                case 27:
                        return 0;
        }
        return 1;
	
}

void colored_screen(char screen[][30],int color[][30],Player* player1)
{
	char *ptr = (char*)malloc(600*sizeof(char));
	char constr[3];constr[2] = '\0';
	char playerchar1[2];playerchar1[1] = '\0';
	*(ptr+599) = '\0';
	strcpy(ptr,"");
	for(int i=0;i<30;i++)
	{	
		strcpy(ptr,"");
		for(int j=0;j<30;j++)
		{	
			if(i==player1->player_y && j==player1->player_x){strcat(ptr,"\x1b[39m");playerchar1[0] = player1->playerchar;strcat(ptr,playerchar1);strcat(ptr,"\x1b[39m ");continue;}
			strcat(ptr,"\x1b[");	
			constr[0] = ((color[i][j] - color[i][j]%10)/10 + '0');
			constr[1] = ((color[i][j]%10) + '0');
			strcat(ptr,constr);strcat(ptr,"m");
			playerchar1[0] = screen[i][j];
			strcat(ptr,playerchar1);
			strcat(ptr,"\x1b[39m ");
		}
		puts(ptr);
		
	}
	free(ptr);

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
        int n;
        char *p;
	char str[30];
        char help[30][30];
        for(int i=0; i<30; i++)
        {
            for(int j=0; j<30; j++)
            {
                if(i==0||i==29||j==0||j==29)help[i][j]='#';
                else help[i][j] = ' ';
            }
        }
        strcpy(str,"- Help -");
        n=10;
        for (p =str;*p!='\0';p++){
            help[3][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"-WASD for movement");
        n=3;
        for (p =str;*p!='\0';p++){
            help[6][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"-You're trapped in the");
        n=3;
        for (p =str;*p!='\0';p++){
            help[8][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"forest you leave by");
        n=4;
        for (p =str;*p!='\0';p++){
            help[9][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"paying $");
        n=4;
        for (p =str;*p!='\0';p++){
            help[10][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"-You can find money by");
        n=3;
        for (p =str;*p!='\0';p++){
            help[12][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"selling items from the");
        n=4;
        for (p =str;*p!='\0';p++){
            help[13][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"forest BUT items will");
        n=4;
        for (p =str;*p!='\0';p++){
            help[14][n] = ("%c",*p);
            n++;
        }
        strcpy(str,"be located randomly");
        n=4;
        for (p =str;*p!='\0';p++){
            help[15][n] = ("%c",*p);
            n++;
        }

        strcpy(str,"- press esc to menu -");
        n=4;
        for (p =str;*p!='\0';p++){
            help[27][n] = ("%c",*p);
            n++;
        }
	
	char *ptr = (char*)malloc(61*sizeof(char));
	*(ptr+60) = '\0';
        for(int i=0; i<30; i++)
        {
            for(int j=0; j<30; j++)
	    {
		*(ptr + 2*j) = help[i][j];
	    }
	    for(int j=1;j<60;j=j+2)*(ptr+j) = ' ';
            puts(ptr);
        }

	free(ptr);
}

void Pause()
{
        char *p;
	char str[30];
        int n;
        char Pause[30][30];
        for(int i=0; i<30; i++)
        {
            for(int j=0; j<30; j++)
            {
                if(i==0||i==29||j==0||j==29)Pause[i][j]='#';
                else Pause[i][j] = ' ';
            }
        }
        strcpy(str,"- Pause -");
        n=10;
        for (p =str;*p!='\0';p++){
            Pause[3][n] = ("%c",*p);
            n++;
        }

        strcpy(str,"Press esc to resume");
        n=6;
        for (p =str;*p!='\0';p++){
            Pause[15][n] = ("%c",*p);
            n++;
        }

        strcpy(str,"Press h for help");
        n=6;
        for (p =str;*p!='\0';p++){
            Pause[18][n] = ("%c",*p);
            n++;
        }

        char *ptr = (char*)malloc(61*sizeof(char));
        *(ptr+60) = '\0';
        for(int i=0; i<30; i++)
        {
            for(int j=0; j<30; j++)
            {
                *(ptr + 2*j) = Pause[i][j];
            }
            for(int j=1;j<60;j=j+2)*(ptr+j) = ' ';
            puts(ptr);
        }

        free(ptr);

}

void EndScreen(int option, int money)
{
	gotoxy(0,0);
	char *ends = (char*)malloc(901*sizeof(char));
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(i==0||i==29||j==0||j==29)*(ends + 30*i + j) = '#';
			else *(ends + 30*i + j) = ' '; 
		}
	}
	if(money >= 100)
	{
		*(ends+311) = 'Y';
		*(ends+312) = 'o';
		*(ends+313) = 'u';
		*(ends+314) = ' ';
		*(ends+315) = 'W';
		*(ends+316) = 'i';
		*(ends+317) = 'n';
	}
	else
	{
		*(ends+311) = 'Y';
                *(ends+312) = 'o';
                *(ends+313) = 'u';
                *(ends+314) = ' ';
                *(ends+315) = 'L';
                *(ends+316) = 'o';
                *(ends+317) = 's';
		*(ends+318) = 'e';
	}
	*(ends+483) = 'R';
	*(ends+484) = 'e';
	*(ends+485) = 's';
	*(ends+486) = 't';
	*(ends+487) = 'a';
	*(ends+488) = 'r';
	*(ends+489) = 't';

	*(ends+498) = 'E';
        *(ends+499) = 'x';
        *(ends+500) = 'i';
        *(ends+501) = 't';

	for(int i=0;i<30;i++)
                {
                        for(int j=0;j<30;j++)
                        {
                                printf("%c ",*(ends+ i*30 + j));
                                switch(option)
                                {
                                        case 0:
                                                if( i*30+j == 482)
						{
                                                        printf("\x1b[2D");
                                                        printf(">");
                                                        printf("\x1b[1C");
                                                        printf("\e[91m");
                                                }
                                                if( i*30+j == 490)
                                                {
                                                        printf("\e[0m");
                                                }
                                                break;
                                        case 1:
                                                if( i*30+j == 497){
                                                        printf("\x1b[2D");
                                                        printf(">");
                                                        printf("\x1b[1C");
                                                        printf("\e[91m");
                                                }
                                                if( i*30+j == 502)
                                                {
                                                        printf("\e[0m");
                                                }
						break;
				}
			}
			printf("\n");
		}
	free(ends);
	gotoxy(0,0);
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
