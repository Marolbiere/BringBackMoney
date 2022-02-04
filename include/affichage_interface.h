#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

void affichage_titre() { //Affiche le template du menu avec titre et box ! 
    clear();
    box(stdscr, 0,0); 
    int xMax = getmaxx(stdscr);                                            
    mvprintw(3,(xMax/2) - 82/2,"  ____       _               ____             _      __  __                        ");
    mvprintw(4,(xMax/2) - 82/2," |  _ \\     (_)             |  _ \\           | |    |  \\/  |                       ");
    mvprintw(5,(xMax/2) - 82/2," | |_) |_ __ _ _ __   __ _  | |_) | __ _  ___| | __ | \\  / | ___  _ __   ___ _   _ ");
    mvprintw(6,(xMax/2) - 82/2," |  _ <| '__| | '_ \\ / _` | |  _ < / _` |/ __| |/ / | |\\/| |/ _ \\| '_ \\ / _ | | | |");
    mvprintw(7,(xMax/2) - 82/2," | |_) | |  | | | | | (_| | | |_) | (_| | (__|   <  | |  | | (_) | | | |  __| |_| |");
    mvprintw(8,(xMax/2) - 82/2," |____/|_|  |_|_| |_|\\__, | |____/ \\__,_|\\___|_|\\_\\ |_|  |_|\\___/|_| |_|\\___|\\__, |");
    mvprintw(9,(xMax/2) - 82/2,"                      __/ |                                                   __/ |");
    mvprintw(10,(xMax/2) - 82/2,"                     |___/                                                   |___/ ");

}

void bordures(int size_x) { //Affichage des bordures
    for (int a = 0; a < size_x + 2; a++) {
        if(a == 0)                printw("\t\t\t\t\t|");
        else if (a == size_x + 1) printw("|\n");
        else                      printw("-");
    }
}

void affichage_carte(char carte[SIZE_X][SIZE_Y]){ //affichage de la carte   
    printw("\n");
    bordures(SIZE_X);
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++) {
            
            if (j == SIZE_X - 1) {
                if(carte[i][j] == 'P')
                    printw(" |\n");
                else
                    printw("%c|\n", carte[i][j]);
            }
            else if(j == 0)  {       
                if(carte[i][j] == 'P')   
                    printw("| ");
                else
                    printw("\t\t\t\t\t|%c", carte[i][j]);
            }
            else { 
                if(carte[i][j] == 'P') 
                    printw(" ");
                else
                    printw("%c", carte[i][j]);
            }
        }
    }
    bordures(SIZE_X);
 }

void interface_joueur(s_player *Joueur) { //interface du joueur en dessous de la carte 
    printw("\t\t\t\t\tLife : %d/5\n",Joueur->life);
    printw("\t\t\t\t\tMoney : %d\n",Joueur->coins);
    printw("\t\t\t\t\tKey : %d\n",Joueur->nb_key);
    printw("\t\t\t\t\t%s\n",Joueur->mess);
    //printw("Dans Buissons (1 : Oui / 0 : Non) : %d\n", Joueur->J_buissons);
    box(stdscr,0,0);

}

void interface_cabane(s_player *Joueur, char carte[SIZE_Y][SIZE_X], int new_pos_y, int new_pos_x) {
    /*-----Rentre le joueur dans la cabane-----*/
    carte[Joueur->pos_y][Joueur->pos_x] = ' ';
    carte[new_pos_y][new_pos_x] = 'A';
    Joueur->J_cabane = 1;
    clear();
    affichage_carte(carte);                  
    interface_joueur(Joueur);   
    /*----------------------------------------*/


    //Affichage de l'interface cabane avec gestion de dépôt de pièces
    int po_x = 65;
    int flag_interface = 0;
    int temp_piece = 0;
    char key;
    while(flag_interface!=1) {
        clrtoeol();
        /*---------------------------Affichage des informations essentiels---------------------------*/
        mvprintw(10, po_x,"Bienvenue dans votre interface cabane !");
        mvprintw(11, po_x,"Vous avez actuellement %d pieces sur vous", Joueur->coins);
        mvprintw(12, po_x,"Vous avez actuellement %d pieces dans votre cabane.", Joueur->cabane_coins);
        mvprintw(14, po_x,"Appuyez sur 'e' pour quitter la cabane.");
        mvprintw(15, po_x,"Appuyez sur 'p' pour ajouter des pieces.");
        /*-------------------------------------------------------------------------------------------*/
        key = tolower(getch()); //Récupère la touche pressée
        switch (key) 
        {
        case 'p':   
            if((Joueur->coins)>0) {
                echo();
                mvprintw(17, po_x,"Combien de pieces voulez vous deposer ? : ");
                wscanw(stdscr,"%d", &temp_piece);
                noecho();
                if(temp_piece<=Joueur->coins) {
                    Joueur->cabane_coins += temp_piece;
                    Joueur->coins -= temp_piece;
                }
                else {
                    mvprintw(17, po_x,"Vous avez entree trop de pieces !"); 
                }
            }
            else {
                mvprintw(17, po_x,"Malheuresement vous n'avez pas de pieces sur vous");
            }
            break;
        case 'e':
            flag_interface = 1;
            Joueur->J_cabane = 0;
            carte[Joueur->pos_y][Joueur->pos_x] = 'J';
            carte[new_pos_y][new_pos_x] = 'H';
            break;
        }
    }
}
