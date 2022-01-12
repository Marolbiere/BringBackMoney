#include <curses.h>

int main()
{
    initscr();
    noecho();
    cbreak();

    int c;
    while ((c=getch())!=27)
        printw("%d ",c);
    return 0;
}

/*char getkey() {
    char key;
    while(1) {
        key = getch();
        if(key == 'z' || key =='q' || key =='s' || key =='d')
        {
            return key;
        }
    }
}*/

/*int main()
{
    //NCURSE START
    initscr();
    noecho();
    cbreak();


    while(1) {
        char touche = getkey();
        
        switch (touche)
        {
        case 'z':
            move(0,0);
            printw("j'avance en z\n");
            break;
        case 'q':
            move(0,0);
            printw("j'avance en q\n");
            break;
        case 's':
            move(0,0);
            printw("j'avance en s\n");
            break;
        case 'd':
            move(0,0);
            printw("j'avance en d\n");
            break;
        }
    }
}*/

