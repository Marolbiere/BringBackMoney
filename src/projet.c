#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <ctype.h>

char get_char() { //Fonction global de relevé de caractère
    char direction;
    while(1) {
        direction = tolower(getch());
        if(direction == 'z' || direction == 'q' || direction == 's' || direction == 'd' || direction == 'i' || direction == 'p' || direction =='e') 
            return direction;
    }
}

#define MAX_MONSTER 5
#define SIZE_X 20
#define SIZE_Y 20
#define RANDOMIZER_SEED srand(time(NULL))

char alea(int min, int max) {
    return rand()%(max + 1 - min) + min;
}

#include "../include/Struct.h" //Import du headerfiles struct
#include "../include/init_carte.h" //Import du headerfiles des init_carte
#include "../include/affichage_interface.h" //Import des fonction gérant les interface et l'affichage
#include "../include/interaction.h" //Import des fonctions d'interactions et de mouvement


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

int main()  {
    char carte[SIZE_X][SIZE_Y]; //Déclaration du tableau stockant la carte du jeu

    //-----Initialisation du terminal Curses----//
    initscr();
    noecho();
    cbreak();
    scrollok(stdscr, TRUE);
    nodelay(stdscr, TRUE); //evite le retour chariot du getch
    //------------------------------------------//

    //---Initialisation des Monstre et du Joueur---//
    s_monster TabMonstre[MAX_MONSTER];
    s_player Joueur;
    //---------------------------------------------//        

    init_player(&Joueur);
    init_carte(carte, &Joueur, TabMonstre); //Fonction d'initialisation de la carte (cf init_carte.h)

    while(Joueur.life!=0) {
        clear();                                 //Clear le terminal
        printw("====Bring Back Money=====\n\n"); //titre
        affichage_carte(carte);                  //Fonction affichant la carte et ses bordures
        interface_joueur(&Joueur, TabMonstre);               //Fonction affichant l'interface du joueur (Vie, pièces etc..)
        input_player(carte, &Joueur);            //Fonction d'évenement pour voir ou se déplace le joueur
        Type_Monstre(carte, TabMonstre, &Joueur);
        
        getch();
    }

    //Message de loose
    clear();
    while(Joueur.life==0) {
        mvprintw(14, 30,"Oh non t'es mové");
        getch();
    }
}