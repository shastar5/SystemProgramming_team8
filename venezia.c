#include <curses.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct drop_word{
	int exist;
	char words[10];
	int row;
	int col;
}drop_word;

int length=0;
int score=0;
int scoreText[3];
int life = 10;
char lifeText[2];
int j=0, i=0;
int sleep_time = 1;

char word[50][10] = {"apple","bus","truck","exam","best",
        "awful","awesome", "computer", "linux", "data", 
	"bat", "adult", "birth", "resource", "score",
	"type", "vegetable", "tea", "tax", "tongue",
	"absent", "careful", "flat", "main", "print",
	"length", "integer", "double", "string", "solar",
	"straight", "silly", "rapid", "cure", "deliver",
	"draw", "force", "gain", "remain", "review", 
	"scream", "pray", "tear", "vote", "smell",
	"ahead", "handle", "include", "press", "push"};
drop_word *drop;

void init_venezia()
{
	length = 0;
	score = 0;
	life = 10;
	strcpy(scoreText, "0");
	strcpy(lifeText, "0");
	j = 0;
	i = 0;
}
void makeDrop()
{
	int col = 0;
	if(i<50)
	{	
	col = rand()%(COLS-10);
	move(0, col);
	drop[i].row = 0;
	drop[i].col = col;
	drop[i].exist = true;
	strcpy(drop[i++].words, word[rand()%50]);
	}
}


void print(void *none)
{
	int k;
	int t = sleep_time;
	
	while( (life > 0) && ((score+10-life)!=50) )
	{
		makeDrop();
		for(j=0;j<i;j++)
		{
			if(drop[j].row>LINES-3)
				continue;
			move(drop[j].row,0);
			for(k=0; k<COLS; k++)
				addstr(" ");				
			if(drop[j].exist == true)
			{
				move(drop[j].row,drop[j].col);
				addstr(drop[j].words);
				if(j==49)
				{
					move(drop[j].row-1, 0);
					for(k=0; k<COLS; k++)
						addstr(" ");
				}
				if(drop[j].row == LINES-3)
				{
					drop[j].exist = false;
					strcpy(drop[j].words, "");
					life--;
					move(LINES-1, COLS-4);
					addstr("   ");
					sprintf(lifeText, "%d", life);
					move(LINES-1, COLS-4);
					addstr(lifeText);
					if(life<=0)
						break;
				}
			}
			else
			{
				if(j==49)
				{
					move(drop[j].row-1, 0);
					for(k=0; k<COLS; k++)
						addstr(" ");
				}	
			}
			drop[j].row++;
			move(LINES-1, (COLS-1)/2+length);
			refresh();
			if((score+10-life)==50)
				break;
		}
		move(LINES-1, (COLS-1)/2);
		sleep(t);
	}
}
void find(char *str)
{
	int k=0;
	for(j=0; j<i; j++)
	{
		if(drop[j].exist == true && !strcmp(drop[j].words, str))
		{
			drop[j].exist = false;
			strcpy(drop[j].words, "");
			score++;
			move(LINES-1, 6);
			addstr("  ");
			move(LINES-1, 6);
			sprintf(scoreText, "%d", score*100);
			addstr(scoreText);
			return;
		}
	}
}

void venezia_game(){	
	pthread_t t1;
	char input[20]= {0};
	int o;
	int k;
	srand( (unsigned)time(NULL) );
	drop = (drop_word*)malloc(sizeof(drop_word)*50);
	
	init_venezia();

	clear();
	move(LINES-2, 0);
	for(k=0; k<COLS-1; k++)
	{
		addstr("-");
	}
	move(LINES-1, 0);
	addstr("score:");
	sprintf(scoreText, "%d", score*100);
	addstr(scoreText);
	move(LINES-1,(COLS-1)/2-7);
	addstr("Enter:");
	move(LINES-1, COLS-9);
	addstr("life:");
	sprintf(lifeText, "%d", life);
	addstr(lifeText);

	refresh();
	pthread_create(&t1, NULL, print, NULL);
	while(life>0 && (score+10-life) != 50){
		for(length = 0; length < 20;)
		{
			if( (life<=0) || ((score+10-life)==50) )
				break;
			o = getch();
			if( (life<=0) || ((score+10-life)==50) )
				break;
			if(o == '\n')
			{
				input[length] = '\0';
				find(input);

				for(k=0; k<20; k++)
				{
					input[k] = '\0';
				}
				move(LINES-1, 0);
				addstr("score:");
				move(LINES-1,(COLS-1)/2-7);
				addstr("Enter:");
				for(k=0; k<=length;k++)
					addstr(" ");
				move(LINES-1, COLS-9);
				addstr("life:");
				move(LINES-1, (COLS-1)/2);
				break;
			}
			else if ( o == 127)
			{
				if( length > 0)
				{
					input[--length] = '\0';
					move(LINES-1, (COLS-1)/2);
					addstr("               ");
					move(LINES-1, (COLS-1)/2);
					addstr(input);
				}
				else
				{
					move(LINES-1, (COLS-1)/2);
					addstr("               ");
					move(LINES-1, (COLS-1)/2);
				}
			}
			else
			{
				input[length++] = o;
				move(LINES-1, (COLS-1)/2);
				addstr(input);
			}
			refresh();
			if(life<0)
				break;
		}
		if( (score+10-life) == 50)
			break;
	}
	free(drop);
	clear();
	move((LINES-1)/2, (COLS-1)/2);
	if(life>0)
	{
		addstr("Congratulation!");
		move((LINES-1)/2+1, (COLS-1)/2);
		addstr("Score: ");
		sprintf(scoreText, "%d", score*100);
		addstr(scoreText);
	}
	else
		addstr("Game Over");
	move(LINES-1, (COLS-1)/2);
	addstr("Press Any Key");
	refresh();
	getch();
}

