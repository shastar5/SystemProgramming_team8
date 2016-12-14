#include <curses.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

typedef struct drop{
	char words[10];
	int row;
	int col;
}drop;

void venezia_game(){
        int i=0, j=0 , life=5, col, row=0;
        srand( (unsigned)time(NULL) );
        char word[10][50] = {"apple","bus","truck","exam","best",
        "awful","awesome", "computer", "linux", "data"};
        drop drop[50];
        time_t start, end;

	start=clock();
        while(1){
		clear();
		end = clock();	
                if( (int)((float)(end-start)/CLOCKS_PER_SEC)/4 == 0 )
                {
			col = rand()%100;
			move(0, col);
			drop[i].row = 0;
			drop[i].col = col;
			strcpy(drop[i].words, word[rand()%10]);
			addstr(drop[i++].words);
			for(j=0 ; j<i ; j++)
			{
				move(drop[j].row, drop[j].col);
				addstr(drop[j].words);
			}
			if(i>50)
				return;
			
                }
		refresh();
		fflush(stdout);	
		sleep(3);
		clear();
		for(j=0 ; j < i ; j++)
		{
			move(++drop[j].row, drop[j].col);
			addstr(drop[j].words);
		}
		refresh();
		fflush(stdout);
		move(LINES-1, 92);
		printf("life=%d",life);
		move(LINES-1, 50);
		refresh();
		fflush(stdout);
		sleep(5);
		
	}
}
