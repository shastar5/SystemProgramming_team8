#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>


void init();
void type_practice();
//void crmode();
//void noecho();

int main(void)
{
	int c;

	initscr();
	start_color();//터미널 글자색과 바탕색 초기화
	init_pair(1, COLOR_RED, COLOR_BLACK);
	//cursres 호출

	fflush(stdin);
	init();

	while(1) {
		c = getchar();
		if(c == '1') {
			venezia_game();
		}

		else if(c == '2')
			type_practice();
		else if(c == '0') {
			endwin();
			exit(0);
		}
		else {
			addstr("\b");
			refresh();
		}
		init();
	}

	endwin();
	
}

void type_practice(){
	int i=0,j=0;
	char c[2]=" ";
	int space = 3;
	int end = 10;

	char pr[11][100] = {
		"The difficulty in life is the choice.",
		"Give me liberty or give me death.",
		"Example is better than precept.",
		"Friend in need is friend indeed.",
		"The family is one of nature's masterpieces.",
		"Our ideals are our better selves.",
		"Power is dangerous unless you have humility.",
		"Books cannot never teach the use of books.",
		"Slow and steady win the game.",
		"Patience is the key to paradise."}; //가독하기 쉽게 행별로 줄 나눔

	//setting
	clear();
	for(j=0 ; j<10 ; j++){
		move(j*3,space); //move 내에서는 무조건 j에는 *3을 붙이기 바람
		addstr(pr[j]); //행렬 내부에선 j만 적음
	}
	move(1,space);
	refresh();
	j=0;
	i=space;
	
	//짜다보니 j는 행렬이 기준이고 i는 커서 기준이 되어버렸습니다.
	//헷갈리지 않도록 주의 바랍니다.	

	//start
	while(1) {
		c[0] = getchar();
		if( strcmp(c[0],'\b') == 0 && i != 0){
			move(j*3,i-1);
			addstr("");
			move(j*3, i-1);
		}
		else if( c[0] != pr[j][i-space] ) {//틀렸을 경우
                        move(j*3,i);
			attron(COLOR_PAIR(1));//터미널색과 글자색 변경
			addch(pr[j][i-space]);
			attroff(COLOR_PAIR(1));//터미널색과 글자색 복구
                        move((j*3)+1,i);
                        addch(c[0]);

			refresh();
                }
		else {//맞을 경우
			addch(c[0]);
			refresh();
		}

		i++; //커서 한 칸 옆으로
		move((j*3)+1,i);
		//문장의 끝에서 다음 줄로
		if(pr[j][i-space] == '\0'){
			i = space; //space는 앞의 여백임
			j++; //j는 배열 기준이라서 1만 증가
			move((j*3)+1,i); //j*3은 화면 기준이라 *3을 추가
		}
		//마지막 문장 판별
		/*
		if(pr[j][0] == '\0'){
			break;
		}
		*/
		refresh();
		if(j == end)
			break;
	}
}

void init()
{
	clear();

	move(8, 10);
	addstr("Type Practice!");
	move(10, 10);
	addstr("Press 1 for Venezia game");
	move(11, 10);
	addstr("Press 2 for type practicing");
	move(12, 10);
	addstr("Press 0 for exit");
	move(14, 10);
	addstr("Input: ");
	refresh();
}

