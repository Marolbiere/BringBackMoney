#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 100000
#define SIZE 100
#define NUMS_TO_GENERATE 10

struct Player { //Information du joueur
    int life;
    int key;
    int position_x;
    int position_y;
    int coins;
    int cabane_coins;
};

int getrand() {
    srand(time(NULL));
    return rand() % 10;
}

void init_carte(int x, int y) { //fonction d'initialisation de carte*
    char map[x][y];

    //complète la carte de caractère
    for (int a = 0; a < y; a++)
    {
        for (int b = 0; b < x; b++)
        {
            map[a][b] = ' ';
        }
    }

    for (int a = 0; a < y; a++)
    {
        for (int b = 0; b < x; b++)
        {
            map[a][0] = '|';
            map[a][y-1] = '|';
            //map[0][a + 1] = '-';
            map[x-1][a + 1] = '-';
        }
    }

    printf("test : %c\n\n", map[x-1][y-1]);
    //printf("test : %s\n\n", map);
    
    //affichage de la carte
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < x; j++) 
        {
            if (j == x - 1) {
                printf("%c\n", map[i][j]);
            }
            else {
                printf("%c", map[i][j]);
            }
            //printf("i = %d, j = %d\n",i,j);
        }
    }
 }

int main() {

    system("cls");
    printf("Bring Back Money\n\n"); //titre
    init_carte(20,20);
    
    return 0;
}