#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"


int scoring(char pos[][8]){

    int score = 0;

    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            char current_piece = pos[i][j];

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