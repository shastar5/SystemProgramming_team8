#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>
void init();
void type_practice();
void venezia_game();

//void crmode();
//void noecho();

int main(void)
{
	int c;

	initscr();
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

	}

	endwin();
	
}

void type_practice(){
	int i=0,j=0;
	char c[2]=" ";
	int space = 3;
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
		if(c[0] != pr[j][i-space]){
                        move(j*3,i);
                        addstr("/");
                        move((j*3)+1,i);
                        addstr(c);
                }
		else {
			addstr(c);
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
	}
}
void venezia_game(){ 


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

