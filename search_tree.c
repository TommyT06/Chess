#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "king.h"
#include "checkmate.h"
#include "scoring.h"
#include <string.h>
#include <ctype.h>



char* find_move(char pos[8][8], int white, int depth, struct stats stats){


    //printf("%d", depth);
    struct stats current;

    copy_stats(&current, stats);

    char return_pos[8][8];

    int score; 
    int best_score;

    if (white == 0){
       best_score = 10000000; 
    }
    else {
    best_score = -10000000;
    }

    char test_pos[8][8];

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
                    copy_stats(&current, stats);
                    if (new_piece(test_pos, i, j, king_x, king_y, current)){
                    if ((isupper(test_pos[king_y][king_x]) && islower(test_pos[j][i])
                    || (islower(test_pos[king_y][king_x]) && isupper(test_pos[j][i])
                    ) || test_pos[king_y][king_x] == '.')){
                        //char temp_dest = test_pos[king_y][king_x];
                        //char temp_init = test_pos[j][i];
                        test_pos[king_y][king_x] = test_pos[j][i];
                        test_pos[j][i] = '.';
                        if (!check(test_pos, white, -10, -10, 0)){
                           
                            if (depth == 0 ){
                                char* best_pos = find_move(test_pos, 1, 1, current);
                                char new_pos[8][8];
                                for (int l = 0; l <8; l++){
                                    for (int p = 0; p < 8; p++){
                                        new_pos[l][p] = *(best_pos+(8*l)+p);
                                    }
                                }
                                score = scoring(new_pos);
                                printf("%d", white);
                            }
                            else {
                                score = scoring(test_pos);
                                printf("%d", white);
                            }

                            if (white == 0){
                                if (score < best_score){
                                    best_score = score;
                                    //printf("Score: %d", score);
                                    for (int g = 0; g < 8; g++){
                                        for (int h = 0; h < 8; h++){
                                            return_pos[g][h] = test_pos[g][h];
                                        }
                                    } 
                                }
                            }
                            else{
                                if (score > best_score){
                                    best_score = score;
                                    //printf("Score: %d", score);
                                    for (int g = 0; g < 8; g++){
                                        for (int h = 0; h < 8; h++){
                                            return_pos[g][h] = test_pos[g][h];
                                        }
                                    } 
                                }
                            }
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

    return return_pos;
}