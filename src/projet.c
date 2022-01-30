#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <ctype.h>

char get_char() { //Fonction global de relevé de caractère
    char C;
    while(1) {
        C = tolower(getch()); //récupérer uniquement en minuscule
        if(C == 'z' || C == 'q' || C == 's' || C == 'd' || C == 'i' || C == 'p' || C =='e' || C =='a' || C =='c' || C == 10) 
            return C;
    }
}

#define MAX_MONSTER 5
#define SIZE_X 20
#define SIZE_Y 20
#define RANDOMIZER_SEED srand(time(NULL))

char alea(int min, int max) { //Fonction générale aléatoire
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

void affichage_titre() {
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
void Game() {
//---Initialisation des Monstre, Joueur, carte---//
    char carte[SIZE_X][SIZE_Y];
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
        input_player(carte, &Joueur, TabMonstre);            //Fonction d'évenement pour voir ou se déplace le joueur
        Type_Monstre(carte, TabMonstre, &Joueur);
    }
    //Message de loose
    clear();
    mvprintw(14,30,"Rah Mince tu as perdu, reessaye un coup");

}
int main()  {
    
    //-----Initialisation du terminal Curses----//
    initscr();
    noecho();
    cbreak(); //Pas besoin d'appuyer sur entrée pour valider une touche
    scrollok(stdscr, TRUE); //Impossible de scroll le terminal ! 
    //------------------------------------------//
    char choice;
    int xMax = getmaxx(stdscr);
    affichage_titre();
    mvprintw(20, (xMax/2) - 23/2, "-->ENTREE POUR JOUER<--");
    mvprintw(22, (xMax/2) - 35/2, "(c) COMMANDE | (a) ABOUT | (q) EXIT");

    while((choice =get_char()) != 'q') {
        switch (choice) {
            case 'c': 
                affichage_titre();
                mvprintw(12, 5, "Commande de mouvement :");
                mvprintw(13, 7, "- Z : HAUT");
                mvprintw(14, 7, "- Q : GAUCHE");
                mvprintw(15, 7, "- S : BAS");
                mvprintw(16, 7, "- D : DROITE");
                mvprintw(18, 5, "Commande d'interaction':");
                mvprintw(19, 7, "- I : Interagir avec certains objets.");
                mvprintw(20, 7, "- E : Sortir de la cabane.");
                mvprintw(20, 7, "- P : Inserer des pieces dans la cabane.");
                break;
            case 'a':
                affichage_titre();
                mvprintw(12, 5, "Bring Back Money !");
                mvprintw(13, 5, "Recuperez un maximum de pieces avant de mourir");
                mvprintw(14, 5, "interagissez avec un monde rempli de caracteres !");
                mvprintw(15, 5, "Description : ");
                mvprintw(16, 7, "- \'J\' : Le joueur qu il faut deplacer sur la carte.");
                mvprintw(17, 7, "- \'O\' : Les pieces a collecter (collecte automatique).");
                mvprintw(18, 7, "- \'C\' : Des coffres qui peuvent soit contenir soit des pieces, soit des pieges.");
                mvprintw(19, 7, "- \'K\' : Des cles pour ouvrir les coffres.");
                mvprintw(20, 7, "- \'G\' : De l herbe qui permet de se cacher d un monstre intelligent.");
                mvprintw(21, 7, "- \'X\' : Un obstacle qui empêche la bonne circulation du joueur.");
                mvprintw(22, 7, "- \'H\' : Le spot de depart du joueur. Le joueur peut stocker des pieces dans la ");
                mvprintw(23,15,"cabane sans que les monstres puissent lui voler.");
                break;
            case 10:
                Game();
                break;

        }
        getch();
    }
}

