#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"
#include "checkmate.h"

int count_pieces(char pos[][8]);

int pawn_pts[8][8]= {
    0, 50, 10, 5, 0, 5, 5, 0, 
    0, 50, 10, 5, 0, -5, 10, 0,
    0, 50, 20, 10, 0, -10, 10, 0,
    0, 50, 30, 25, 25, 0, -20, 0,
    0, 50, 30, 25, 25, 0, -20, 0,
    0, 50, 20, 10, 0, -10, 10, 0,
    0, 50, 10, 5, 0, -5, 10, 0,
    0, 50, 10, 5, 0, 5, 5, 0,
};
int knight_pts[8][8]= {
    -50, -40, -30, -30, -30, -30, -40, -50, 
    -40, -20, 0, 5, 0, 5, -20, -40,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -30, 0, 15, 20, 20, 15, 5, -30,
    -30, 0, 15, 20, 20, 15, 5, -30,
    -30, 0, 10, 15, 15, 10, 0, -30,
    -40, -20, 0, 5, 0, 5, -20, -40,
    -50, -40, -30, -30, -30, -30, -40, -50,
};
int bishop_pts[8][8]= {
    -20, -10, -10, -10, -10, -10, -10, -20, 
    -10, 0, 0, 5, 0, 10, 5, -10,
    -10, 0, 5, 5, 10, 10, 0, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 0, 10, 10, 10, 10, 0, -10,
    -10, 0, 5, 5, 10, 10, 0, -10,
    -10, 0, 0, 5, 0, 10, 5, -10,
    -20, -10, -10, -10, -10, -10, -10, -20,
};
int rook_pts[8][8]= {
    0, 5, -5, -5, -5, -5, -5, 0, 
    0, 10, 0, 0, 0, 0, 0, 0,
    0, 10, 0, 0, 0, 0, 0, 0,
    0, 10, 0, 0, 0, 0, 0, 5,
    0, 10, 0, 0, 0, 0, 0, 5,
    0, 10, 0, 0, 0, 0, 0, 0,
    0, 10, 0, 0, 0, 0, 0, 0,
    0, 5, -5, -5, -5, -5, -5, 0,
};
int queen_pts[8][8]= {
    -20, -10, -10, -5, 0, -10, -10, -20, 
    -10, 0, 0, 0, 0, 5, 0, -10,
    -10, 0, 5, 5, 5, 5, 5, -10,
    -5, 0, 5, 5, 5, 5, 0, -5,
    -5, 0, 5, 5, 5, 5, 0, -5,
    -10, 0, 5, 5, 5, 5, 0, -10,
    -10, 0, 0, 0, 0, 0, 0, -10,
    -20, -10, -10, -5, -5, -10, -10, -20,
};
int king_pts_mid[8][8]= {
    -30, -30, -30, -30, -20, -10, 20, 20, 
    -40, -40, -40, -40, -30, -20, 20, 30,
    -40, -40, -40, -40, -30, -20, 0, 10,
    -50, -50, -50, -50, -40, -20, 0, 0,
    -50, -50, -50, -50, -40, -20, 0, 0,
    -40, -40, -40, -40, -30, -20, 0, 30,
    -40, -40, -40, -40, -30, -20, 20, 20,
    -30, -30, -30, -30, -20, -10, 20, 20,
};
int king_pts_late[8][8]= {
    -50, -30, -30, -30, -30, -30, -30, -50, 
    -40, -20, -10, -10, -10, -10, -30, -30,
    -30, -10, 20, 30, 30, 20, 0, -30,
    -20, 0, 30, 40, 40, 30, 0, -30,
    -20, 0, 30, 40, 40, 30, 0, -30,
    -30, -10, 20, 30, 30, 20, 0, -30,
    -40, -20, -10, -10, -10, -10, -30, -30,
    -50, -30, -30, -30, -30, -30, -30, -50,
};



int location_check(char, int, int);
int scoring(char pos[][8], struct stats stats){

    int score = 0;

    for (int i = 0; i < 8; i++){
        //printf("\n");
        for (int j = 0; j < 8; j++){
            char current_piece = pos[i][j];
            //printf("%c", pos[i][j]);
            if (current_piece == '.'){
                continue;
            }
            //int location_score = location_check(current_piece, j, i);

            switch (current_piece)
            {
            case 'p':
                score -= 100;
                score -= pawn_pts[j][7-i];
                break;
            case 'P':
                score += 100;
                score += pawn_pts[j][i];
                break;
            case 'b':
                score -= 300;
                score -= bishop_pts[j][7-i];
                break;
            case 'n':
                score -= 300;
                score -= knight_pts[j][7-i];
                break;
            case 'B':
                score += 300;
                score += bishop_pts[j][i];
                break;
            case 'N':
                score += 300;
                score += knight_pts[j][i];
                break;
            case 'Q':
                score += 900;
                score += queen_pts[j][i];
                break;
            case 'q':
                score -= 900;
                score -= queen_pts[j][7-i];
                break;
            case 'R':
                score += 500;
                score += rook_pts[j][i];
                break;
            case 'r':
                score -= 500;
                score -= rook_pts[j][7-i];
                break;
            case 'k':
            if (check(pos, 0, j, i)){
                if (checkmate(pos, 0, stats)){
                    score += 20000;
                }
            }
            // else {
            //     if (checkmate(pos, 0, stats)){

            //         score += 20000;
            //     }
            // }

            if (count_pieces(pos) < 15){
                score -= king_pts_late[j][7-i];
            }
            else {
                score -= king_pts_mid[j][7-i];
            }

            break;
            case 'K':
            if (check(pos, 1, j, i)){
                if (checkmate(pos, 1, stats)){
                    score -= 20000;
                }
            }
            else {
                if (checkmate(pos, 1, stats)){
                    score += 20000;
                }
            }

            if (count_pieces(pos) < 15){
                score += king_pts_late[j][i];
            }
            else {
                score += king_pts_mid[j][i];
            }

            break;
            default:
                break;
            }
        }
    }

    return score;
}

// int location_check(char piece, int x, int y){

//     int score = 0;

//     else if (piece == 'K' || piece == 'k'){
//         if (piece == 'K'){
//             if (y == 7){
//                 score += 5;
//             }
//             else {
//                 score -= 5;
//             }

//             if (x <= 1 || x >= 6){
//                 score += 5;
//             }
//         }
//         if (piece == 'k'){
//             if (y == 0){
//                 score += 5;
//             }
//             else {
//                 score -= 5;
//             }

//             if (x <= 1 || x >= 6){
//                 score += 5;
//             }
      
//         }
//     }

//     else {
//         if (piece == 'P'){
//             score -= y + 1;
//         }
//         if (piece == 'p'){
//             score += y - 1;
//         }
//         if (x >= 2 && x <= 5 && y >= 2 && y <= 5){
//             score += 3;
//         }
//         else if (x == 1 || x == 6){
//             score += 1;
//         }
//     }
//     return score;
// }

int count_pieces(char pos[][8]){

    int count = 0;

    for (int i = 0; i < 8; i++){
        for (int j =0; j < 8; j++){
            if (pos[i][j] != '.'){
                count++;
            }
        }
    }

    return count;

}