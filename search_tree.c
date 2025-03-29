#include <stdio.h>
#include <stdlib.h>
#include "moves.h"
#include "king.h"
#include "checkmate.h"
#include "scoring.h"
#include <string.h>
#include <ctype.h>
#include "struct.h"




struct MOVE alphaBetaMin(char pos[8][8], int white, int depth, struct stats stats, int alpha, int beta);
struct MOVE alphaBetaMax(char pos[8][8], int white, int depth, struct stats stats, int alpha, int beta){

    struct stats current;
    struct MOVE next_move;
    struct MOVE move_to_make;

    copy_stats(&current, stats);

    int best_score;

    best_score = 2000000;

    char test_pos[8][8];
    int i,j, o, z;
    int king_x;
    int king_y;
    for (i = 0; i < 8; i++){
        for (j = 0; j < 8; j++){
            test_pos[j][i] = pos[j][i];
        }
    }

    if (depth == 0) {
        next_move.score = scoring(test_pos, current);
        return next_move;
    }
                            

    for (i = 0; i < 8; i++){
        for (j = 0; j <8; j++){
            if (white == 1){
                if (!isupper(pos[j][i])){
                    continue;
                }
                if (pos[j][i] == 'K'){
                    if (check(pos, 1, i, j)){
                        if (checkmate(pos, 1, current)){
                            next_move.score = scoring(pos, current);
                            return next_move;
                        }
                    }
                    else {
                        if (checkmate(pos, 1, current)){
                            next_move.score = scoring(pos, current);
                            return next_move;
                        }
                    }
                }
            }
            else{
                if (!islower(pos[j][i])){
                    continue;
                }
                if (pos[j][i] == 'k'){
                    if (check(pos, 0, i, j)){
                        if (checkmate(pos, 0, current)){
                            next_move.score = scoring(pos, current);
                            return next_move;
                        }
                    }
                    else {
                        if (checkmate(pos, 0, current)){
                            next_move.score = scoring(pos, current);
                            return next_move;
                        }
                    }
                }
            }
            for (king_x = 0; king_x < 8; king_x++){
                for (king_y = 0; king_y <8; king_y++){

                    if (king_x == i && king_y == j){
                        continue;
                    }


                    copy_stats(&current, stats);
                    if (piece(test_pos, i, j, king_x, king_y, &current)){
                    if ((isupper(test_pos[king_y][king_x]) && islower(test_pos[j][i]))
                    || (islower(test_pos[king_y][king_x]) && isupper(test_pos[j][i])
                    ) || test_pos[king_y][king_x] == '.'){
                        test_pos[king_y][king_x] = test_pos[j][i];
                        test_pos[j][i] = '.';
                        if (!check(test_pos, white, -10, -10)){  
                            if (depth != 0){
                                next_move = alphaBetaMin(test_pos, !white, depth-1, current, alpha, beta);
                            }
                            if (depth == 0) {
                                next_move.score = scoring(test_pos, current);
                                return next_move;
                            }
                            
                                if (next_move.score < best_score){
                                    best_score = next_move.score;
                                    if (next_move.score < alpha){
                                        alpha = next_move.score;
                                    }
                                    move_to_make.dest_x = king_x;
                                    move_to_make.dest_y = king_y;
                                    move_to_make.start_x = i;
                                    move_to_make.start_y = j; 
                                    move_to_make.score = next_move.score;
                                    next_move.dest_x = king_x;
                                    next_move.dest_y = king_y;
                                    next_move.start_x = i;
                                    next_move.start_y = j; 
                                    
                                }
                                if (next_move.score <= beta){
                                    i = 8;
                                    j = 8;
                                    king_x = 8;
                                    king_y = 8;
                                    break;
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
    return move_to_make;
}

struct MOVE alphaBetaMin(char pos[8][8], int white, int depth, struct stats stats, int alpha, int beta){

    struct stats current;
    struct MOVE next_move;
    struct MOVE move_to_make;

    copy_stats(&current, stats);

    int best_score;

    if (white == 0){
       best_score = 2000000; 
    }
    else {
        best_score = -2000000;
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

    if (depth == 0) {
        next_move.score = (scoring(test_pos, current));
        return next_move;
    }
                            

    for (i = 0; i < 8; i++){
        for (j = 0; j <8; j++){
            if (white == 1){
                if (!isupper(pos[j][i])){
                    continue;
                }
            }
            else{
                if (!islower(pos[j][i])){
                    continue;
                }
            }
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
                    if (piece(test_pos, i, j, king_x, king_y, &current)){
                    if ((isupper(test_pos[king_y][king_x]) && islower(test_pos[j][i]))
                    || (islower(test_pos[king_y][king_x]) && isupper(test_pos[j][i])
                    ) || test_pos[king_y][king_x] == '.'){
                        test_pos[king_y][king_x] = test_pos[j][i];
                        test_pos[j][i] = '.';
                        if (!check(test_pos, white, -10, -10)){  
                            if (depth != 0){
                                next_move = alphaBetaMax(test_pos, !white, depth-1, current, alpha, beta);
                            }
                            if (depth == 0) {
                                next_move.score = scoring(test_pos, current);
                                return next_move;
                            }
                            if (next_move.score > best_score){
                                best_score = next_move.score;
                                if (next_move.score > beta){
                                     beta = next_move.score;
                                }
                                
                                move_to_make.dest_x = king_x;
                                move_to_make.dest_y = king_y;
                                move_to_make.start_x = i;
                                move_to_make.start_y = j;
                                move_to_make.score = next_move.score;
                                next_move.dest_x = king_x;
                                next_move.dest_y = king_y;
                                next_move.start_x = i;
                                next_move.start_y = j;  
                                if (next_move.score >= alpha){
                                    i = 8;
                                    j = 8;
                                    king_x = 8;
                                    king_y = 8;
                                    break;
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

    return move_to_make;
}

