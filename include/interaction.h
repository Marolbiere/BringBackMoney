#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <curses.h>

#define SIZE_X 20
#define SIZE_Y 20
#define RANDOMIZER_SEED srand(time(NULL))


void interaction_environnement(int new_pos_y, int new_pos_x, char carte[SIZE_X][SIZE_Y], s_player *Joueur) {

    switch (carte[new_pos_y][new_pos_x])
    {
    //Cases où on peut passer dessus
    case 'O':
        if (Joueur->J_buissons == 1) {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->J_buissons = 0;
        }
        else {
            Joueur->coins+=1;
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
        }
        Joueur->pos_x = new_pos_x;
        Joueur->pos_y = new_pos_y;
        break;
    case 'G':
        if(Joueur->J_buissons == 0) {
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->J_buissons = 1;
        }
        else{
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->J_buissons = 1;
        }
        Joueur->pos_x = new_pos_x;
        Joueur->pos_y = new_pos_y;
        break;
    case 'C':
        if(Joueur->nb_key>=1) {
            RANDOMIZER_SEED;
            int p_or_c = rand()%SIZE_X;
            if(p_or_c %2 == 0) { Joueur->coins += 1;}
            else               { Joueur->life -= 1; }
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->pos_x = new_pos_x;
            Joueur->pos_y = new_pos_y;
            Joueur-> nb_key -=1;
        }
        break;
    case 'K':
        if (Joueur->J_buissons == 1) {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->J_buissons = 0;
        }
        else {
            Joueur->nb_key+=1;
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
        }
        Joueur->pos_x = new_pos_x;
        Joueur->pos_y = new_pos_y;
        break;
    case 'H':
        interface_cabane(Joueur);
        break;
    case 'X':
        break;
    case 'P':
        RANDOMIZER_SEED;
        int random = rand()%SIZE_Y;
        if(random<SIZE_X/2 && random > 0) {
            Joueur->life-=1;
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->pos_x = new_pos_x;
            Joueur->pos_y = new_pos_y;
        }
        else {
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = ' ';
            carte[Joueur->poscab_y][Joueur->poscab_x - 1] = 'J';
            Joueur->pos_y = Joueur->poscab_y;
            Joueur->pos_x = Joueur->poscab_x - 1;
        }
        break;
    //Cases de bases (espaces)
    default:
        if (Joueur->J_buissons == 1) {
            carte[Joueur->pos_y][Joueur->pos_x] = 'G';
            carte[new_pos_y][new_pos_x] = 'J';
            Joueur->J_buissons = 0;
        }
        else {
            carte[Joueur->pos_y][Joueur->pos_x] = ' ';
            carte[new_pos_y][new_pos_x] = 'J';
        }
        Joueur->pos_x = new_pos_x;
        Joueur->pos_y = new_pos_y;
        break;
    }
}

void input_player(char carte[SIZE_X][SIZE_Y], s_player *Joueur) {
    char direction = get_char();

    int var_x = 0;
    int var_y = 0;
    //int var_interaction = 0;
    switch (direction) {
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
            /*if(verif_case(carte,Joueur,'C')) {
                //ouverture_coffre(Joueur);
                RANDOMIZER_SEED;
                int p_or_c = rand()%SIZE_X;
                if(p_or_c %2 == 0) { Joueur->coins += 1;}
                else               { Joueur->life -= 1; }
            }*/
            break;
    }

    int new_pos_x = Joueur->pos_x + var_x;
    int new_pos_y = Joueur->pos_y + var_y;
    interaction_environnement(new_pos_y,new_pos_x,carte,Joueur);
}