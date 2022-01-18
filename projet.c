#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
//#include <conio.h> 

#include "Struct.h" //Import du headerfiles struct
#include "init_carte.h" //Import du headerfiles des init_carte

#define SIZE_X 20
#define SIZE_Y 20

//Joueur        J      Le joueur qu’il faut déplacer sur la carte.
//Pièce d’or    O      Les pièces à collecter (collecte automatique).
//Coffre        C      Des coffres qui peuvent soit contenir soit des pièces, soit des pièges.
//Clé           K      Des clés pour ouvrir les coffres.
//Cabane        H      Le spot de départ du joueur. Le joueur peut stocker des pièces dans la cabane sans que les monstres puissent lui voler.
//Piège         P      Caché au départ, il n’apparait pas sur la carte jusqu’à ce qu’il soit découvert. Les effets sont variables: (cf pdf).
//Obstacle      X      Un obstacle qui empêche la bonne circulation du joueur.
//Herbe         G      De l’herbe qui permet de se cacher d’un monstre intelligent.


void init_player(s_player *Joueur) {
    //Création du joueur
    Joueur->life = 5;
    Joueur->J_buissons = 0;
    Joueur->coins = 0;
    Joueur->cabane_coins = 27;
}

char get_char() {
    char direction;
    while(1) {
        direction = getch();
        if(direction == 'z' || direction == 'q' || direction == 's' || direction == 'd' || direction == 'i') 
            return direction;
    }
}

void bordures(int size_x) {
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
            if (j == SIZE_X - 1)    printw("%c|\n", carte[i][j]);
            else if(j == 0)         printw("|%c", carte[i][j]);
            else                    printw("%c", carte[i][j]);
        }
    }
    bordures(SIZE_X);
 }
 
void interface_cabane() {
    while(1) {
        printw("Bienvenue dans l'interface cabane \n");
        //getch();
    }
}

void interaction_environnement(char key, char carte[SIZE_X][SIZE_Y], s_player *Joueur) {
    int temp_piece = 0;
    int var_x = 0;
    int var_y = 0;
    //int var_interaction = 0;
    switch (key) {
        case 'z': 
            if(Joueur->pos_y != 0) {var_y = -1;}
            break;
        case 'q': 
            if(Joueur->pos_x != 0) {var_x = -1;}
            break;
        case 's':
            if(Joueur->pos_y != SIZE_Y - 1) {var_y = 1;}
            break;
        case 'd': if(Joueur->pos_x != SIZE_X - 1) {var_x = 1;} 
            break;
        case 'i': 
            if(carte[Joueur->pos_y - 1][Joueur->pos_x] == 'H' || carte[Joueur->pos_y + 1][Joueur->pos_x] == 'H' || carte[Joueur->pos_y][Joueur->pos_x - 1] == 'H' || carte[Joueur->pos_y][Joueur->pos_x + 1] == 'H') {
                //clear();
                while(1) {
                    nodelay(stdscr, FALSE);
                    move(13, 40);
                    printw("Bienvenue dans votre interface cabane ! ");
                    move(14, 40);
                    printw("Voici vos pieces stocker : %d", Joueur->cabane_coins);
                    move(15, 40);
                    printw("Combien de pieces voulez vous mettre : ");
                    move(16, 40);
                    wscanw(stdscr,"%d", &temp_piece);
                    if(Joueur->coins>0) {
                        Joueur->coins-= temp_piece;
                        Joueur->cabane_coins+= temp_piece;
                    }
                    else{
                        move(17, 40);
                        printw("Vous n'avez plus de pieces sur vous !");
                    }
                }
            }
    }


    switch (carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x])
    {
    case 'O':
        if (Joueur->J_buissons == 1 && carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] == 'O') {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
            Joueur->J_buissons = 0;
        }
        else {
            Joueur->coins+=1;
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
        }
        break;
    
    case 'G':
        if(carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] == 'G' && Joueur->J_buissons == 0) {
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
            Joueur->J_buissons = 1;
        }
        else if(carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] == 'G' && Joueur->J_buissons == 1) {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
            Joueur->J_buissons = 1;
        }
        break;
    case 'H':
        break;
    case 'X':
        break;
    default:
        if (Joueur->J_buissons == 1 && carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] == ' ') {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
            Joueur->J_buissons = 0;
        }
        else {
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[Joueur->pos_y + var_y][Joueur->pos_x + var_x] = 'J';
        }
        break;
    }
}

void mouvement_player(char carte[SIZE_X][SIZE_Y], s_player *Joueur) {
    char direction = get_char();
    //recherche des coordonnées du joueur
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            if(carte[i][j] == 'J') {
                Joueur->pos_x = j;
                Joueur->pos_y = i;
            }
        }
    }
    interaction_environnement(direction, carte, Joueur);
}

void affichage_interface(s_player *Joueur) {
    printw("Life : %d/5\n",Joueur->life);
    printw("Money : %d\n",Joueur->coins);
    printw("Time Before the end :\n");
}


int main()  {
    char carte[SIZE_X][SIZE_Y];                  //Déclaration du tableau stockant la carte du jeu

    //-----Initialisation du terminal Curses----//
    initscr();
    noecho();
    cbreak();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE); //evite le retour chariot du getche
    //------------------------------------------//
    
    struct Squelette_Player Joueur;

    
    init_carte(carte);                           //Fonction d'initialisation de la carte (cf init_carte.h)
    init_player(&Joueur);

    while(1) {
        clear();                                 //Clear le terminal
        printw("====Bring Back Money=====\n\n"); //titre
        affichage_carte(carte);                  //Fonction affichant la carte et ses bordures
        affichage_interface(&Joueur);              //Fonction affichant l'interface du joueur (Vie, pièces etc..)
        mouvement_player(carte, &Joueur);                 //Fonction d'évenement pour voir ou se déplace le joueur
        
        getch();
    }


    
}