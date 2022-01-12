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
 
struct Player Joueur1;

void init_player() {
    //Création du joueur
    Joueur1.life = 5;
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
 

void interaction_environnement(char key, char carte[SIZE_X][SIZE_Y]) {
    int var_x = 0;
    int var_y = 0;
    int var_i = 0;
    switch (key) {
        case 'z': 
            if(Joueur1.pos_y != 0) {var_y = -1;}
            break;
        case 'q': 
            if(Joueur1.pos_x != 0) {var_x = -1;}
            break;
        case 's':
            if(Joueur1.pos_y != SIZE_Y - 1) {var_y = 1;}
            break;
        case 'd': if(Joueur1.pos_x != SIZE_X - 1) {var_x = 1;} 
            break;
        case 'i': var_i = 1;
            break;
    }

    if(var_i==1) {
        printw("J'interagis avec quelque chose\n");
    }

    if(carte[Joueur1.pos_y + var_y][Joueur1.pos_x + var_x] != 'X') {
        if(carte[Joueur1.pos_y + var_y][Joueur1.pos_x + var_x] == 'O')
                Joueur1.coins+=1;

        carte[Joueur1.pos_y][Joueur1.pos_x] = ' ';
        carte[Joueur1.pos_y + var_y][Joueur1.pos_x + var_x] = 'J';
    }
}

char getkey() {
    char key;
    while(1) {
        key = getch();
        if(key == 'z' || key =='q' || key =='s' || key =='d')
        {
            return key;
        }
    }
}

void mouvement_player(char carte[SIZE_X][SIZE_Y]) {
    char direction = getkey();
    //recherche des coordonnées du joueur
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            if(carte[i][j] == 'J') {
                Joueur1.pos_x = j;
                Joueur1.pos_y = i;
            }
        }
    }
    interaction_environnement(direction, carte);
}

void affichage_interface() {
    printw("Life : %d/5\n",Joueur1.life);
    printw("Money : %d\n",Joueur1.coins);
    printw("Time Before the end :\n");
}


int main()  {
    char carte[SIZE_X][SIZE_Y]; //Déclaration du tableau stockant la carte du jeu

    //init_curses
    initscr();
    noecho();
    cbreak();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE); //evite le retour chariot du getche
    
    init_carte(carte);  

    while(1) {
        clear();
        printw("====Bring Back Money=====\n\n"); //titre
        affichage_carte(carte);
        affichage_interface(carte);
        mouvement_player(carte);
        
        getch();
    }


    
}