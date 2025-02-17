#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "king.h"
#include "moves.h"

// int change(char pos[][8], int white){

//     int not_mate = 0;

//     char king;
//     if (white == 1){
//         king = 'K';
//     }
//     else {
//         king = 'k';
//     }
//     int i,j;
//     int king_x;
//     int king_y;

//         for (i = 0; i < 8; i++){
//             for (j = 0; j < 8; j++){
//                 if (pos[i][j] == king){
//                     king_x = j;
//                     king_y = i;
//                     break;
//                 } 
//             }
//         }


//     pos[king_y][king_x] = '.';
//     //Check if king can move
//     if (white == 1){
//         if (!check(pos, white, king_x+1, king_y, 0) && !isupper(pos[king_y][king_x+1])){
//             printf("4");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x, king_y+1, 0) && !isupper(pos[king_y+1][king_x])){
//             printf("6");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y, 0) && !isupper(pos[king_y][king_x-1])){
//             printf("8");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x, king_y-1, 0) && !isupper(pos[king_y-1][king_x])){
//             printf("2");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x+1, king_y+1, 0) && !isupper(pos[king_y+1][king_x+1])){
//             printf("5");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y+1, 0) && !isupper(pos[king_y+1][king_x-1])){
//             printf("7");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x+1, king_y-1, 0) && !isupper(pos[king_y-1][king_x+1])){
//             printf("3");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y-1, 0) && !isupper(pos[king_y-1][king_x-1])){
//             printf("1");
//             not_mate = 1;  
//         }
//     }
//     else if (white == 0){
//         if (!check(pos, white, king_x+1, king_y, 0) && !islower(pos[king_y][king_x+1])){
//             printf("4");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x, king_y+1, 0) && !islower(pos[king_y+1][king_x])){
//             printf("6");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y, 0) && !islower(pos[king_y][king_x-1])){
//             printf("8");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x, king_y-1, 0) && !islower(pos[king_y-1][king_x])){
//             printf("2");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x+1, king_y+1, 0) && !islower(pos[king_y+1][king_x+1])){
//             printf("5");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y+1 ,0) && !islower(pos[king_y+1][king_x-1])){
//             printf("7");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x+1, king_y-1, 0) && !islower(pos[king_y-1][king_x+1])){
//             printf("3");
//             not_mate = 1;
//         }
//         if (!check(pos, white, king_x-1, king_y-1, 0) && !islower(pos[king_y-1][king_x-1])){
//             printf("1");
//             not_mate = 1;
//         } 
//     }

//     int blockable_x;
//     int blockable_y;


//     if (check_straight(pos, king_x, king_y, white, 1,0, 0)){
//         if (block_straight(pos, king_x, king_y, white, 1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_straight(pos, king_x, king_y, white, -1,0, 0)){
//         if (block_straight(pos, king_x, king_y, white, -1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_straight(pos, king_x, king_y, white, 0, 1, 0)){
//         if (block_straight(pos, king_x, king_y, white, 0, 1)){
//             not_mate = 1; 
//         }
//     }
//     if (check_straight(pos, king_x, king_y, white, 0, -1,0)){
//         if (block_straight(pos, king_x, king_y, white, 0, -1)){
//             not_mate = 1;
//         }
//     }
    
//     if (check_diagonal(pos, king_x, king_y, white, -1,1,0)){
//         if (block_diagonal(pos, king_x, king_y, white, -1, 1)){
//             not_mate = 1;
//         }
//     }
//     if (check_diagonal(pos, king_x, king_y, white, 1,-1,0)){
//         if (block_diagonal(pos, king_x, king_y, white, 1, -1)){
//             not_mate = 1;
//         }
//     }
//     if (check_diagonal(pos, king_x, king_y, white, 1,1,0)){
//         if (block_diagonal(pos, king_x, king_y, white, 1, 1)){
//             not_mate = 1;
//         }
//     }
//     if (check_diagonal(pos, king_x, king_y, white, -1,-1,0)){
//         if (block_diagonal(pos, king_x, king_y, white, -1, -1)){
//             not_mate = 1;
//         }
//     }


//     if (check_knight(pos, king_x, king_y, white, 2, 1)){
//         if (check(pos, white, king_x+2, king_y+1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, -2, 1)){
//         if (check(pos, white, king_x-2, king_y+1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, 2, -1)){
//         if (check(pos, white, king_x+2, king_y-1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, -2, -1)){
//         if (check(pos, white, king_x-2, king_y-1, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, 1, 2)){
//         if (check(pos, white, king_x+1, king_y+2, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, -1, -2)){
//         if (check(pos, white, king_x-1, king_y-2, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, -1, 2)){
//         if (check(pos, white, king_x-1, king_y+2, 0)){
//             not_mate = 1;
//         }
//     }
//     if (check_knight(pos, king_x, king_y, white, 1, -2)){
//         if (check(pos, white, king_x+1, king_y-2, 0)){
//             not_mate = 1;
//         }
//     }



//     if (not_mate == 1){
//         pos[king_y][king_x] = king;
//         return 0;
//     }

//     return 1;
// }



// int block_straight(char pos[][8], int king_x, int king_y, int white, int vert, int hor){

//     int colour_check = 0;
//     int double_check = 0;
//     char temp = 0;
//     if (white == 0){
//          colour_check = 1;
//     }

//     int stop = 0;
//     while(stop == 0){
//         king_x = king_x + hor;
//         king_y = king_y + vert;
//         if (pos[king_y][king_x] != '.'){
//             stop = 1;
//         }
//         if (check(pos, colour_check, king_x, king_y, 1)){
//             return 1;
//         }
//     }
//     return 0;
// }

// int block_diagonal(char pos[][8], int king_x, int king_y, int white, int vert, int hor){
    
//     int colour_check = 0;
//     if (white ==0){
//         colour_check = 1;
//     }

//     int stop = 0;

//     while (stop == 0){
//         king_x = king_x+hor;
//         king_y = king_y+vert;
        
//         while(stop == 0){
//         king_x = king_x + hor;
//         king_y = king_y + vert;
//         if (pos[king_y][king_x] != '.'){
//             stop = 1;
//         }
//         if (check(pos, colour_check, king_x, king_y, 1)){
//             return 1;
//         }
//         }
//     }

//     return 0;
// }



int checkmate(char pos[][8], int white){

    int not_mate = 0;

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
                    if (piece(test_pos, i, j, king_x, king_y)){
                    if ((isupper(test_pos[king_y][king_x]) && islower(test_pos[j][i]))
                    || (islower(test_pos[king_y][king_x]) && isupper(test_pos[j][i])
                    ) || test_pos[king_y][king_x] == '.'){
                        char temp_dest = test_pos[king_y][king_x];
                        char temp_init = test_pos[j][i];
                        test_pos[king_y][king_x] = test_pos[j][i];
                        test_pos[j][i] = '.';
                        if (!check(test_pos, white, -10, -10, 0)){
                            for (int i = 0; i <8; i++){
                                for (int j = 0; j < 8; j++){
                                    printf("%c", test_pos[i][j]);
                                }
                                printf("\n");
                            }

                            printf("switch");
                            not_mate = 1; 
                        }
                        
                        for (z = 0; z< 8; z++){
                            for (o = 0; o < 8; o++){
                                test_pos[o][z] = pos[o][z];
                            }
                        }

                        if (not_mate == 1){
                            printf("\nNot Mate\n");
                            return 0;
                        }
                    }
                    }
                }
            }
        }
    }
    printf("\nMate\n");
    return 1;
}
