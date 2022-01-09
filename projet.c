#include <stdlib.h>
#include <stdio.h>
#include <time.h>
//#include <ncurse.h>
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
        if(a == 0)                printf("|");
        else if (a == size_x + 1) printf("|\n");
        else                      printf("-");
    }
}

 void affichage_carte(char carte[SIZE_X][SIZE_Y]){ //affichage de la carte
    
    bordures(SIZE_X);
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++) {
            if (j == SIZE_X - 1)    printf("%c|\n", carte[i][j]);
            else if(j == 0)         printf("|%c", carte[i][j]);
            else                    printf("%c", carte[i][j]);
        }
    }
    bordures(SIZE_X);
 }
 
char get_char_moove() {
    char var_char;
    printf("Quelle direction voulez vous allez ? (Z/Q/S/D)\n");
    scanf("%c",&var_char);
    return var_char;
}

void check_coins(char key, char carte[SIZE_X][SIZE_Y]) {
    int var_x = 0;
    int var_y = 0;
    if(key=='z')     { var_y = -1; }
    else if(key=='s'){ var_y =  1; }
    else if(key=='q'){ var_x = -1; }
    else if(key=='d'){ var_x =  1; }

    if(carte[Joueur1.pos_y + var_y][Joueur1.pos_x + var_x] == 'O')
                Joueur1.coins+=1;

}

int check_obstacle(char key, char carte[SIZE_X][SIZE_Y]) {
    int var_x = 0;
    int var_y = 0;
    if(key=='z')     {  var_y = -1; }
    else if(key=='s'){  var_y = 1 ; }
    else if(key=='q'){  var_x = -1; }
    else if(key=='d'){  var_x = 1 ; }

    if(carte[Joueur1.pos_y + var_y][Joueur1.pos_x + var_x] == 'X')
        return 1;
    else
        return 0;

}

void mouvement_player(char carte[SIZE_X][SIZE_Y]) {
    char direction = get_char_moove();
    printf("direction choisie : %c",direction);
    //recherche des coordonnées du joueur
    for (int i = 0; i < SIZE_Y; i++)
    {
        for (int j = 0; j < SIZE_X; j++)
        {
            //printf("\nTEST_BOUCLE : j = %d / i = %d\n", j,i);
            if(carte[i][j] == 'J') {
                Joueur1.pos_x = j;
                Joueur1.pos_y = i;
                //printf("\nTEST_BOUCLE : Coordonées du joueur trouvé !\n");
            }
            
        }
    }
    //printf("\nTEST_FONCTION : Pos X : %d / Pos Y : %d\n",Joueur1.pos_x,Joueur1.pos_y);

    switch (direction)
    {
    case 'z':
        if(Joueur1.pos_y != 0) {
            if(check_obstacle(direction, carte) == 0) {
                carte[Joueur1.pos_y][Joueur1.pos_x] = ' ';
                check_coins(direction,carte);
                carte[Joueur1.pos_y - 1][Joueur1.pos_x] = 'J';
            }
        }
        break;
    case 'q':
        if (Joueur1.pos_x != 0) {
            if(check_obstacle(direction, carte) == 0) {
                carte[Joueur1.pos_y][Joueur1.pos_x] = ' ';
                check_coins(direction,carte);
                carte[Joueur1.pos_y][Joueur1.pos_x - 1] = 'J';
            }
        }
        break;
    case 's':
        if (Joueur1.pos_y != SIZE_Y - 1) {
        if(check_obstacle(direction, carte) == 0) {
                carte[Joueur1.pos_y][Joueur1.pos_x] = ' ';
                check_coins(direction,carte);
                carte[Joueur1.pos_y + 1][Joueur1.pos_x] = 'J';
            }
        }
        break;
    case 'd':
        if (Joueur1.pos_x != SIZE_X - 1) {
            if(check_obstacle(direction, carte) == 0) {
                carte[Joueur1.pos_y][Joueur1.pos_x] = ' ';
                check_coins(direction,carte);
                carte[Joueur1.pos_y][Joueur1.pos_x + 1] = 'J';
            }
        }
        break;
    }
}

void affichage_interface() {
    printf("Life : %d/5\n",Joueur1.life);
    printf("Money : %d\n",Joueur1.coins);
    printf("Time Before the end :\n");
}

int main() {
    char carte[SIZE_X][SIZE_Y]; //Déclaration du tableau stockant la carte du jeu

    system("cls");    
    printf("====Bring Back Money=====\n\n"); //titre

    init_carte(carte);
    init_player();
    affichage_carte(carte);
    affichage_interface();
    while(1==1) {
        mouvement_player(carte);
        system("cls");
        printf("====Bring Back Money=====\n\n"); //titre
        affichage_carte(carte);
        affichage_interface();
        printf("\nPOSITION DU JOUEUR : pos_x = %d / pos_y = %d\n", Joueur1.pos_x, Joueur1.pos_y);
    }

    return 0;
}