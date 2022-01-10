#include <curses.h> 
#define X 5
#define Y 5

struct Player1 {
    int pos_x;
    int pos_y;
};

struct Player1 Joueur;

void affichage_carte() {

}

int main()
{
    char carte[Y][X];
    
    for (int i = 0; i < Y; i++)
    {
        for (int j = 0; j < X; j++)
        {
            if(i == (Y-1) && j == (X-1))
                carte[i][j] = "J";
            else
                carte[i][j] = " ";            
        }
    }

    initscr();
    noecho();
    raw();
    int c;
    while((c = getch()) != 27)
    {
        switch (c)
        {
        case 'z':
            carte[4][4];
            carte[4+1][4] = "J";
            break;

        }



        move(2,0);
        printw("Keycode: %d, and the character: %c", c, c);
        move(0,0);
        printw("Write something (ESC to escape): ");
        refresh();
    }
    endwin();
    return 0;
}