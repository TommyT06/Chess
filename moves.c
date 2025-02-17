#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "king.h"

static int en_p = 0;
static int en_p_y = -10;
static int unMovW_k = 1;
static int unMovB_k = 1;
static int unMovW_RL = 1;
static int unMovW_RR = 1;
static int unMovB_RL = 1;
static int unMovB_RR = 1;

static int counter = 0;

void check_queen(char pos[][8], int, int,int, int, char);
int check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y);
int check_str(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y);
int piece(char pos[][8], int cur_x, int cur_y , int dest_x, int dest_y){

    if (en_p != 0){
        counter++;
    }
    if (counter == 2){
        counter = 0;
        en_p = 0;
    }
    //printf("%c %c %d %d %d %d\n", pos[cur_y][cur_x], pos[dest_y][dest_x], cur_x, cur_y, dest_x, dest_y);
    int first;

    switch (pos[cur_y][cur_x]){
        
        case 'p':
            if (cur_y == 1){
                first = 1;
            }
            else{
                first = 0;
            }

            if (first == 1){
                if (cur_y + 1 == dest_y || cur_y + 2 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.' && pos[cur_y+1][cur_x] == '.'){
                            if (dest_y == 3){
                                en_p = dest_x;
                                en_p_y = dest_y-1;
                            }
                            return 1;  
                        }
                    }
                }
            }
            else if (first == 0){
                if (cur_y + 1 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.'){
                            check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'b');
                            return 1;  
                        }
                    }
                }
            }

            if (cur_y + 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){
                if (dest_x == en_p && dest_y == en_p_y){
                    pos[dest_y-1][dest_x] = '.';
                    return 1;
                }
                if (pos[dest_y][dest_x] != '.'){
                    check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'b');
                    return 1;
                }
            }
            else{
                return 0;
            }

            break;
        case 'P':
            if (cur_y == 6){
                first = 1;
            }
            else{
                first = 0;
            }

            if (first == 1){
                if (cur_y - 1 == dest_y || cur_y - 2 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.' && pos[cur_y-1][cur_x] == '.'){
                            if (dest_y == 4){
                                en_p = dest_x;
                                en_p_y = dest_y+1;
                            }
                            return 1;  
                        }
                    }
                }
            }
            else if (first == 0){
                if (cur_y - 1 == dest_y){
                    if (dest_x == cur_x){
                        if (pos[dest_y][dest_x] == '.'){
                            check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'w');
                            return 1;  
                        }
                    }
                }
            }


            if (cur_y - 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){
                if (dest_x == en_p && dest_y == en_p_y){
                    pos[dest_y+1][dest_x] = '.';
                    return 1;
                }
                if (pos[dest_y][dest_x] != '.'){
                    check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'w');
                    return 1;
                }
            }
            else{
                return 0;
            }
        break;
        case 'N':
        case 'n':
            if (abs(cur_x - dest_x) == 1 && abs(cur_y - dest_y) == 2){
                return 1;
            }
            if (abs(cur_x - dest_x) == 2 && abs(cur_y - dest_y) == 1){
                return 1;
            }
        break;

        case 'b':
        case 'B':
            if (check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                return 1;
            }
            else {
                return 0;
            }
        break;

        case 'r':
            if (check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                if (cur_x == 0){
                    unMovB_RL = 0;
                }
                if (cur_x == 7){
                    unMovB_RR = 0;
                }
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 'R':
            if (check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                if (cur_x == 0){
                    unMovW_RL = 0;
                }
                if (cur_x == 7){
                    unMovW_RR = 0;
                }
                return 1;
            }
            else {
                return 0;
            }
            
        break;
        case 'Q':
        case 'q':
            if (dest_x == cur_x || dest_y == cur_y){
                if (check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            else {
                if (check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            return 0;
        break;
        case 'k':


        // prob some of the worst code i have ever written holy fuck
        // nvm definetly
        // no idea how this works but it does so i aint touching it

            if (unMovB_k == 1){
                if (dest_x == 6 && unMovB_RR == 1){
                    if (!(check(pos, 'k', -10, -10, 0))){
                        char temp_dest = pos[dest_y][dest_x];
                        char temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'k', -10, -10, 0)){
                            pos[dest_y][dest_x] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        temp_dest = pos[dest_y][dest_x-1];
                        temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x-1] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x-1] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        
                        pos[dest_y][dest_x-1] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        if (pos[0][6] == '.' && pos[0][5] == '.'){
                            pos[0][5] = 'r';
                            pos[0][7] = '.';
                            unMovB_k = 0;
                            return 1;
                        }
                    }
                }
                if (dest_x == 2 && unMovB_RL == 1){
                    if (!(check(pos, 'k', -10, -10, 0))){
                        char temp_dest = pos[dest_y][dest_x];
                        char temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'k', -10, -10, 0)){
                            pos[dest_y][dest_x] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        temp_dest = pos[dest_y][dest_x+1];
                        temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x+1] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x+1] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x+1] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        if(pos[0][1] == '.' && pos[0][2] == '.' && pos[0][3] == '.'){
                            pos[0][3] = 'r';
                            pos[0][0] = '.';
                            unMovB_k = 0;
                            return 1;
                        }
                    }
                }
            }

            if (abs(dest_x-cur_x) <= 1 & abs(dest_y-cur_y) <= 1){
                unMovB_k = 0;
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 'K':
            if (unMovW_k == 1){
                if (dest_x == 6 && unMovW_RR == 1){
                    if (!(check(pos, 'K', -10, -10, 0))){
                        char temp_dest = pos[dest_y][dest_x];
                        char temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        temp_dest = pos[dest_y][dest_x-1];
                        temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x-1] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x-1] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x-1] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;

                        if (pos[7][6] == '.' && pos[7][5] == '.'){
                            pos[7][5] = 'R';
                            pos[7][7] = '.';
                            unMovW_k = 0;
                            return 1;
                        }
                    }
                }
                if (dest_x == 2 && unMovW_RL == 1){
                    if (!(check(pos, 'K', -10, -10, 0))){
                        char temp_dest = pos[dest_y][dest_x];
                        char temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        temp_dest = pos[dest_y][dest_x+1];
                        temp_init = pos[cur_y][cur_x];
                        pos[dest_y][dest_x+1] = pos[cur_y][cur_x];
                        pos[cur_y][cur_x] = '.';                        
                        if (check(pos, 'K', -10, -10, 0)){
                            pos[dest_y][dest_x+1] = temp_dest;
                            pos[cur_y][cur_x] = temp_init;
                            return 0;
                        }
                        pos[dest_y][dest_x+1] = temp_dest;
                        pos[cur_y][cur_x] = temp_init;
                        if (pos[7][1] == '.' && pos[7][2] == '.' && pos[7][3] == '.'){
                            pos[7][3] = 'R';
                            pos[7][0] = '.';
                            unMovW_k = 0;
                            return 1;
                        }
                    }
                }
            }

            if (abs(dest_x-cur_x) <= 1 & abs(dest_y-cur_y) <= 1){
                unMovW_k = 0;
                return 1;
            }
            else {
                return 0;
            }
        break;
    }
    return 0;
}

int check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

    int i = 0;
    int j = 0;
    int dif_x = 0;
    int dif_y = 0;
    int x = 0;

    dif_x = abs(cur_x - dest_x);
    dif_y = abs(cur_y - dest_y);

    if (dif_x != dif_y){
        return 0;
    }

    if (dest_x > cur_x){
        i = 1;
    }
    else {
        i = -1;
    }

    if (dest_y > cur_y){
        j = 1;
    }
    else {
        j = -1;
    }
   
    for (x = 1; x < dif_x; x++){
        if (pos[cur_y+(x*j)][cur_x+(x*i)] != '.'){
            return 0;
        }
    }


    return 1;
}

int check_str(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

    int vert = 0;
    int dif = 0;
    int i = 0 ;
    int opp = 1;

    if (cur_x == dest_x){
        vert = 1;
        dif = (dest_y - cur_y);
    }
    else {
        vert = 0;
        dif = (dest_x - cur_x);
    }

    if (dif < 0){
        opp = -1;
        dif = dif * -1;
    }

    if (vert == 0){
        for ( i = 1; i < dif; i++){
            if (pos[cur_y][cur_x+(i*opp)] != '.'){
                return 0;
            }
        }
    }
    else {
        for (i = 1; i<dif; i++){
            if (pos[cur_y+(i*opp)][cur_x] != '.'){
                return 0;
            }
        }
    }

    return 1;
    
}

void check_queen(char pos[][8], int dest_x, int dest_y, int cur_x, int cur_y, char col){

    if (col == 'w'){
        if (dest_y == 0){
            pos[cur_y][cur_x] = 'Q';  
        }
    }

    else if (col == 'b'){
        if (dest_y == 7){
            pos[cur_y][cur_x] = 'q';  
        }
    }

}