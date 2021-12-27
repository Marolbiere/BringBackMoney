#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <conio.h> 

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
 
struct Player { //Information du joueur
    int life;
    int key;
    int position_x;
    int position_y;
    int coins;
    int cabane_coins;
};


void init_carte(char carte[SIZE_X][SIZE_Y]) { //fonction d'initialisation de carte
    int nb_random;
    srand(time(NULL));

    for (int i = 0; i < SIZE_Y; i++) //coordonnées verticale
    {
        for (int j = 0; j < SIZE_X; j++) //coordonnées horizontale
        {
            nb_random = rand() % 20;
            if (nb_random == j)
                carte[i][j] = 'O';
            else
                carte[i][j] = ' ';

            if(j == SIZE_X - 1 && i == SIZE_Y - 1)
                carte[i][j] = 'H';
        }
    }
    printf("random number : %d\n", nb_random);
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
        for (int j = 0; j < SIZE_X; j++) 
        {
            if (j == SIZE_X - 1)    printf("%c|\n", carte[i][j]);
            else if(j == 0)         printf("|%c", carte[i][j]);
            else                    printf("%c", carte[i][j]);
        }
    }
    bordures(SIZE_X);
 }
 
void mouvement() {
    int var_char;
    printf("Pour quitter le jeu appuie sur \"E\" ");  
        while ((var_char = getch()) != EOF && var_char != 'E') {
            switch (var_char)
            {
            case 'z':
                    printf("je bouge en haut\n");
                break;
            case 'q':
                    printf("je bouge a gauche\n");
                break;
            case 's':
                printf("je bouge en bas\n");
                break;
            case 'd':
                    printf("je bouge a droite\n");
                break;
            
            }
        }
}

int main() {
    char carte[SIZE_X][SIZE_Y];
    //system("cls");
    printf("\n====Bring Back Money=====\n\n"); //titre
    //init_carte(carte);
    //affichage_carte(carte);
    mouvement();
    
    return 0;
}