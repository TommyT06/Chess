#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"


int location_check(char, int, int);
int scoring(char pos[8][8]){

    int score = 0;

    

    for (int i = 0; i < 8; i++){
        printf("\n");
        for (int j = 0; j < 8; j++){
            char current_piece = pos[i][j];
            printf("%c", pos[i][j]);
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
                score -= 100;
                break;
            case 'P':
                score += 100;
                break;
            case 'b':
            case 'n':
                score -= 300;
                break;
            case 'B':
            case 'N':
                score += 300;
                break;
            case 'Q':
                score += 900;
                break;
            case 'q':
                score -= 900;
                break;
            case 'R':
                score += 500;
                break;
            case 'r':
                score -= 500;
                break;
            default:
                break;
            }
        }
    }

    printf("Score: %d\n", score);

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

        if ((y == 3 || y == 4 ) && (x == 3 || x == 4)){
            score += 6;
        }
        else if (y >= 2 && y <= 5){
            score += 5;
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