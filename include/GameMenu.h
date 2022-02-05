#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>
#include <ctype.h>


void retour();
void Menu();
void Settings();
void Game();
void GameOver(s_player *Joueur);
void Sauvegarde(s_player *Joueur,char username[20]);


void retour() {
    int yMax, xMax;
    getmaxyx(stdscr,yMax,xMax);
    mvprintw(yMax - 2, (xMax/2)-27/2, "Appuyez sur (r) pour sortir");
    if(tolower(getch()) == 'r')  {
        Menu();
    }
}

void Menu() {
    char choice;
    int xMax = getmaxx(stdscr);
    affichage_titre();
    mvprintw(20, (xMax/2) - 23/2, "-->ENTREE POUR JOUER<--");
    mvprintw(22, (xMax/2) - 45/2, "(c) COMMANDE | (a) A PROPOS | (ECHAP) QUITTER");
    mvprintw(27, (xMax/2) - 28/2, "v1.0.0       Simon Marolleau");

    while((choice = tolower(getch())) != 27) {
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
                retour();
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
                mvprintw(21, 7, "- \'X\' : Un obstacle qui empeche la bonne circulation du joueur.");
                mvprintw(22, 7, "- \'H\' : Le spot de depart du joueur. Le joueur peut stocker des pieces dans la ");
                mvprintw(23,15,"cabane sans que les monstres puissent lui voler.");
                retour();
                break;
            case 10:
                Game();
                break;
        }
    }
}

void Settings() {
    i_settings Settings;
    echo();
    affichage_titre();
    mvprintw(17, 30,"Taille de la carte ? (initialement 20 par 20) : en y : ");
    wscanw(stdscr,"%d", &Settings.coord[0]);
    affichage_titre();
    mvprintw(17, 30,"Taille de la carte ? (initialement 20 par 20) : en x : ");
    wscanw(stdscr,"%d", &Settings.coord[1]);
    noecho();
}

void Game() {
    //---Initialisation des Monstre, Joueur, carte---//
    char carte[SIZE_Y][SIZE_X];
    s_monster TabMonstre[MAX_MONSTER];
    s_player Joueur;
    //---------------------------------------------//        

    init_player(&Joueur);
    init_carte(carte, &Joueur, TabMonstre); //Fonction d'initialisation de la carte (cf init_carte.h)

    while(Joueur.life!=0) {
        clear();                                 //Clear le terminal
        affichage_carte(carte);                  //Fonction affichant la carte et ses bordures
        interface_joueur(&Joueur);               //Fonction affichant l'interface du joueur (Vie, pièces etc..)
        input_player(carte, &Joueur, TabMonstre);            //Fonction d'évenement pour voir ou se déplace le joueur
        Type_Monstre(carte, TabMonstre, &Joueur);
    }
    //Direction l'affiche de GameOver
    GameOver(&Joueur);
}
void Sauvegarde(s_player *Joueur, char username[20]) {
    FILE * save; //pointeur de réference au fichier
    save = fopen("src/main.save", "a");
    fprintf(save, "%s\t\t%d\n", username, Joueur->cabane_coins);
    fclose(save);
    if(getch() == 27) // appui sur la touche echap
        endwin(); //Fermeture de la fenètre graphique
}

void GameOver(s_player *Joueur) {
    int xMax = getmaxx(stdscr);
    char username[20];
    affichage_titre();
    //getmaxyx(stdscr, xMax, yMax);
    mvprintw(15, (xMax/2) - 74/2, "Malheureusement les monstres sont arrives a leurs fin...");
    mvprintw(16, (xMax/2) - 74/2, "Neanmoins, jeune joueur, tu peux te relever, nous croyons en toi...");
    echo();
    mvprintw(17, (xMax/2) - 74/2, "Quel est ton nom pour que les anciens se souviennent de toi hero ?"); 
    move(18,(xMax/2) - 10);
    wscanw(stdscr,"%s", username);
    noecho();
    mvprintw(18, (xMax/2) - 74/2, "Merci pour ton aide precieuse. Appuie sur n importe quelle bouton pour revenir au menu"); 
    Sauvegarde(Joueur, username);
    Menu();
}