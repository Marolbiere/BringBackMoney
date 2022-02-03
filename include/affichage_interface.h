#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

void bordures(int size_x) { //Affichage des bordures
    for (int a = 0; a < size_x + 2; a++) {
        if(a == 0)                printw("|");
        else if (a == size_x + 1) printw("|\n");
        else                      printw("-");
    }
}

void affichage_carte(char carte[SIZE_X][SIZE_Y]){ //affichage de la carte   
    bordures(SIZE_X);
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++) {
            
            if (j == SIZE_X - 1) {
                //if(carte[i][j] == 'P')
                //    printw(" |\n");
                //else
                    printw("%c|\n", carte[i][j]);
            }
            else if(j == 0)  {       
                //if(carte[i][j] == 'P')   
                //    printw("| ");
                //else
                    printw("|%c", carte[i][j]);
            }
            else { 
                //if(carte[i][j] == 'P') 
                //    printw(" ");
                //else
                    printw("%c", carte[i][j]);
            }
        }
    }
    bordures(SIZE_X);
 }

void interface_joueur(s_player *Joueur) { //interface du joueur en dessous de la carte 
    printw("Life : %d/5\n",Joueur->life);
    printw("Money : %d\n",Joueur->coins);
    printw("Key : %d\n",Joueur->nb_key);
    printw("Dans Buissons (1 : Oui / 0 : Non) : %d\n", Joueur->J_buissons);

}

void interface_cabane(s_player *Joueur, char carte[SIZE_Y][SIZE_X], int new_pos_y, int new_pos_x) {
    /*-----Rentre le joueur dans la cabane-----*/
    carte[Joueur->pos_y][Joueur->pos_x] = ' ';
    carte[new_pos_y][new_pos_x] = 'A';
    Joueur->J_cabane = 1;
    clear();
    printw("====Bring Back Money=====\n\n");
    affichage_carte(carte);                  
    interface_joueur(Joueur);   
    /*----------------------------------------*/


    //Affichage de l'interface cabane avec gestion de dépôt de pièces
    int flag_interface = 0;
    int temp_piece = 0;
    char key;
    while(flag_interface!=1) {
        clrtoeol();
        /*---------------------------Affichage des informations essentiels---------------------------*/
        mvprintw(10, 30,"Bienvenue dans votre interface cabane !");
        mvprintw(11, 30,"Vous avez actuellement %d pieces sur vous", Joueur->coins);
        mvprintw(12, 30,"Vous avez actuellement %d pieces dans votre cabane.", Joueur->cabane_coins);
        mvprintw(14, 30,"Appuyez sur 'e' pour quitter la cabane.");
        mvprintw(15, 30,"Appuyez sur 'p' pour ajouter des pieces.");
        /*-------------------------------------------------------------------------------------------*/
        key = tolower(getch()); //Récupère la touche pressée
        switch (key) 
        {
        case 'p':   
            if((Joueur->coins)>0) {
                echo();
                mvprintw(17, 30,"Combien de pieces voulez vous deposer ? : ");
                wscanw(stdscr,"%d", &temp_piece);
                noecho();
                if(temp_piece<=Joueur->coins) {
                    Joueur->cabane_coins += temp_piece;
                    Joueur->coins -= temp_piece;
                }
                else {
                    mvprintw(17, 30,"Vous avez entree trop de pieces !"); 
                }
            }
            else {
                mvprintw(17, 30,"Malheuresement vous n'avez pas de pieces sur vous");
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
