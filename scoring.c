#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"


int location_check(char, int, int);
int scoring(char pos[][8]){

    int score = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            char current_piece = pos[i][j];
            if (current_piece == '.'){
                continue;
            }
            int location_score = location_check(current_piece, j, i);
            if (islower(current_piece)){
                score -= location_score;
            }
            else {
                score += location_score;
            }
            switch (current_piece)
            {
            case 'p':
                score -= 1;
                break;
            case 'P':
                score += 1;
                break;
            case 'b':
            case 'n':
                score -= 3;
                break;
            case 'B':
            case 'N':
                score += 3;
                break;
            case 'Q':
                score += 9;
                break;
            case 'q':
                score -= 9;
                break;
            case 'R':
                score += 5;
                break;
            case 'r':
                score -= 5;
                break;
            default:
                break;
            }
        }
    }

    //printf("Score: %d", score);

    return score;
}

int location_check(char piece, int x, int y){

    int score = 0;

    if (piece != 'K' && piece != 'k' && piece != 'p' && piece != 'P'){

        if (x >= 2 && x <= 5 && y >= 2 && y <= 5){
            score += 5;
        }
        else if (x == 1 || x == 6){
            score += 3;
        }
        else {
            score -= 1;
        }

        if ((y == 3 || y == 4 ) && (x == 3 || x == 4)){
            score += 6;
        }
        else if (y >= 2 && y <= 5){
            score += 5;
        }

        if (piece == 'P'){
            score -= y;
        }
        if (piece == 'p'){
            score += y;
        }
    }
    else if (piece == 'K' || piece == 'k'){
        if (piece == 'K'){
            if (y == 7){
                score += 5;
            }
            else {
                score -= 5;
            }

            if (x <= 1 || x >= 6){
                score += 5;
            }
        }
        if (piece == 'k'){
            if (y == 0){
                score += 5;
            }
            else {
                score -= 5;
            }

            if (x <= 1 || x >= 6){
                score += 5;
            }
      
        }
    }

    else {
        if (piece == 'P'){
            score -= y + 1;
        }
        if (piece == 'p'){
            score += y - 1;
        }
        if (x >= 2 && x <= 5 && y >= 2 && y <= 5){
            score += 3;
        }
        else if (x == 1 || x == 6){
            score += 1;
        }
    }
    return score;
}