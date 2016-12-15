#include "head.h"

int main(void)
{
        int c;

        initscr();

		//터미널 글자색과 바탕색 초기화
        start_color();

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

