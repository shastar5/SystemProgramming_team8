#include <stdio.h>
#include <curses.h>
#include <stdlib.h>
#include <termios.h>
#include <string.h>

#ifndef TYPE_PRACTICE_H_
#define TYPE_PRACTICE_H_
void type_practice();
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

#endif
