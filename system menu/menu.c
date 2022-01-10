#include <curses.h>

int main()
{
    //NCURSE START
    initscr();
    noecho();
    cbreak();

    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);

    WINDOW * menuwin = newwin(6, xMax-12,yMax-8, 5);
    box(menuwin, 0,0);
    refresh();
    wrefresh(menuwin);

    endwin();

}