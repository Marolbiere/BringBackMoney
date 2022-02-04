#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <ctype.h>

#define MAX_MONSTER 5
#define MAX_SIZE_Y 100
#define MAX_SIZE_X 100
#define RANDOMIZER_SEED srand(time(NULL))
#define SIZE_X 20
#define SIZE_Y 20

char alea(int min, int max) { //Fonction générale aléatoire
    return rand()%(max + 1 - min) + min;
}

#include "../include/struct.h"              //Import du headerfiles struct
#include "../include/init_carte.h"          //Import du headerfiles des init_carte
#include "../include/affichage_interface.h" //Import des fonction gérant les interface et l'affichage
#include "../include/interaction.h"         //Import des fonctions d'interactions et de mouvement


//Joueur        J      Le joueur qu’il faut déplacer sur la carte.
//Pièce d’or    O      Les pièces à collecter (collecte automatique).
//Coffre        C      Des coffres qui peuvent soit contenir soit des pièces, soit des pièges.
//Clé           K      Des clés pour ouvrir les coffres.
//Cabane        H      Le spot de départ du joueur. Le joueur peut stocker des pièces dans la cabane sans que les monstres puissent lui voler.
//Piège         P      Caché au départ, il n’apparait pas sur la carte jusqu’à ce qu’il soit découvert. Les effets sont variables: (cf pdf).
//Obstacle      X      Un obstacle qui empêche la bonne circulation du joueur.
//Herbe         G      De l’herbe qui permet de se cacher d’un monstre intelligent.


int verif_case(char carte[SIZE_Y][SIZE_X], s_player *Joueur, char caractere) {
    return  carte[Joueur->pos_y - 1][Joueur->pos_x] == caractere || 
            carte[Joueur->pos_y + 1][Joueur->pos_x] == caractere || 
            carte[Joueur->pos_y][Joueur->pos_x - 1] == caractere || 
            carte[Joueur->pos_y][Joueur->pos_x + 1] == caractere;
}

/*-----------------------------Evenement--------------------------*/
#include "../include/GameMenu.h"
/*----------------------------------------------------------------*/

int main()  {
    //-----Initialisation du terminal Curses----//
    initscr();
    noecho();
    cbreak(); //Pas besoin d'appuyer sur entrée pour valider une touche
    scrollok(stdscr, TRUE); //Impossible de scroll le terminal ! 
    //------------------------------------------//
    Menu();
    return 0;
}

