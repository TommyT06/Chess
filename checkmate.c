#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"





void new_check_queen(char pos[][8], int ,int ,int ,int , char);
int new_check_str(char pos[][8], int, int, int, int);
int new_check_diag(char pos[][8], int, int, int, int);
int new_piece(char pos[][8], int, int, int, int, struct stats);

int checkmate(char pos[][8], int white, struct stats game_stats){

    
    struct stats testing;
    copy_stats(&testing, game_stats);

    int not_mate = 0;

    // FILE *fp;
    // fp = fopen("current_positions.txt", "w");

    char test_pos[8][8];

    char king;
    if (white == 1){
        king = 'K';
    }
    else {
        king = 'k';
    }
    int i,j, o, z;
    int king_x;
    int king_y;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            test_pos[j][i] = pos[j][i];
        }
    }

    for (i = 0; i < 8; i++){
        for (j = 0; j <8; j++){
            for (king_x = 0; king_x < 8; king_x++){
                for (king_y = 0; king_y <8; king_y++){

                    if (king_x == i && king_y == j){
                        continue;
                    }

                    if (white == 1){
                        if (!isupper(pos[j][i])){
                            continue;
                        }
                    }
                    else if (!islower(pos[j][i])){
                        continue;
                    }
                    copy_stats(&testing, game_stats);
                    if (new_piece(test_pos, i, j, king_x, king_y, testing)){
                    if ((isupper(test_pos[king_y][king_x]) && islower(test_pos[j][i]))
                    || (islower(test_pos[king_y][king_x]) && isupper(test_pos[j][i])
                    ) || test_pos[king_y][king_x] == '.'){
                        char temp_dest = test_pos[king_y][king_x];
                        char temp_init = test_pos[j][i];
                        test_pos[king_y][king_x] = test_pos[j][i];
                        test_pos[j][i] = '.';
                        if (!check(test_pos, white, -10, -10, 0)){
                            not_mate = 1; 
                        }
                        
                        for (z = 0; z< 8; z++){
                            for (o = 0; o < 8; o++){
                                test_pos[o][z] = pos[o][z];
                            }
                        }
                    }
                    }
                }
            }
        }
    }
    // fclose(fp);
    if (not_mate == 1){
        return 0;
    }
    //printf("\nMate\n");
    return 1;
}




int new_piece(char pos[][8], int cur_x, int cur_y , int dest_x, int dest_y, struct stats testing){

    //printf("%d %d\n", current.en_p, current.en_p_y);

    if (testing.en_p != -100){
        testing.counter++;
    }
    if (testing.counter == 2){
        testing.counter = 0;
        testing.en_p = -100;
        testing.en_p_y = -100;
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
                                testing.en_p = dest_x;
                                testing.en_p_y = dest_y-1;
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
                            new_check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'b');
                            return 1;  
                        }
                    }
                }
            }

            if (cur_y + 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){
                if (dest_x == testing.en_p && dest_y == testing.en_p_y){
                    pos[dest_y-1][dest_x] = '.';
                    return 1;
                }
                if (pos[dest_y][dest_x] != '.'){
                    new_check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'b');
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
                                testing.en_p = dest_x;
                                testing.en_p_y = dest_y+1;
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
                            new_check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'w');
                            return 1;  
                        }
                    }
                }
            }


            if (cur_y - 1 == dest_y && (cur_x + 1 == dest_x || cur_x - 1 == dest_x)){
                if (dest_x == testing.en_p && dest_y == testing.en_p_y){
                    pos[dest_y+1][dest_x] = '.';
                    //printf("ENP");
                    return 1;
                }
                if (pos[dest_y][dest_x] != '.'){
                    new_check_queen(pos, dest_x, dest_y, cur_x, cur_y, 'w');
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
            if (new_check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                return 1;
            }
            else {
                return 0;
            }
        break;

        case 'r':
            if (new_check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                if (cur_x == 0){
                    testing.unMovB_RL = 0;
                }
                if (cur_x == 7){
                    testing.unMovB_RR = 0;
                }
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 'R':
            if (new_check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                if (cur_x == 0){
                    testing.unMovW_RL = 0;
                }
                if (cur_x == 7){
                    testing.unMovW_RR = 0;
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
                if (new_check_str(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            else {
                if (new_check_diag(pos, cur_x, cur_y, dest_x, dest_y)){
                    return 1;
                }
            }
            return 0;
        break;
        case 'k':


        // prob some of the worst code i have ever written holy fuck
        // nvm definetly
        // no idea how this works but it does so i aint touching it

            if (testing.unMovB_k == 1 && dest_y == 0 && cur_y == 0){
                if (dest_x == 6 && testing.unMovB_RR == 1){
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
                            testing.unMovB_k = 0;
                            return 1;
                        }
                    }
                }
                if (dest_x == 2 && testing.unMovB_RL == 1){
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
                            testing.unMovB_k = 0;
                            return 1;
                        }
                    }
                }
            }

            if (abs(dest_x-cur_x) <= 1 && abs(dest_y-cur_y) <= 1){
                testing.unMovB_k = 0;
                return 1;
            }
            else {
                return 0;
            }
            break;
        case 'K':
            if (testing.unMovW_k == 1 && dest_y == 7 && dest_x == 7){
                if (dest_x == 6 && testing.unMovW_RR == 1){
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
                            testing.unMovW_k = 0;
                            return 1;
                        }
                    }
                }
                if (dest_x == 2 && testing.unMovW_RL == 1){
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
                            testing.unMovW_k = 0;
                            return 1;
                        }
                    }
                }
            }

            if (abs(dest_x-cur_x) <= 1 & abs(dest_y-cur_y) <= 1){
                testing.unMovW_k = 0;
                return 1;
            }
            else {
                return 0;
            }
        break;
    }
    return 0;
}

int new_check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

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

int new_check_str(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y){

    int vert = 0;
    int dif = 0;
    int i = 0 ;
    int opp = 1;

    if (!(cur_x == dest_x || cur_y == dest_y)){
        return 0;
    }

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

void new_check_queen(char pos[][8], int dest_x, int dest_y, int cur_x, int cur_y, char col){

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
