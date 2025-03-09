#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int check_straight(char pos[][8], int , int, int , int , int);
int check_diagonal(char pos[][8], int, int, int, int, int);
int check_knight(char pos[][8], int, int, int, int, int);

int check(char pos[][8], int white, int king_x, int king_y, int empty){



    if (king_x == -1 || king_y == -1 || king_x == 8 || king_y == 8){
        return 1;
    }
    else if (king_x == -10 && king_y == -10){
        char king;
        if (white == 1){
            king = 'K';
        }
        else {
            king = 'k';
        }
        int i,j;

        for (i = 0; i < 8; i++){
            for (j = 0; j < 8; j++){
                if (pos[i][j] == king){
                    king_x = j;
                    king_y = i;
                } 
            }
        }
        
    }

    if (white == 1){
            if ((pos[king_y-1][king_x+1] == 'p')  || pos[king_y-1][king_x-1] == 'p'){
                return 1;
            }
        }
    else {
            if (pos[king_y+1][king_x+1] == 'P' || pos[king_y+1][king_x-1] == 'P'){
                return 1;
            }
    }

    if (white == 1){
            if (pos[king_y+1][king_x] == 'k'){
                return 1;
            }
            if (pos[king_y][king_x+1] == 'k'){
                return 1;
            }
            if (pos[king_y-1][king_x] == 'k'){
                return 1;
            }
            if (pos[king_y][king_x-1] == 'k'){
                return 1;
            }
            if (pos[king_y+1][king_x+1] == 'k'){
                return 1;
            }
            if (pos[king_y+1][king_x-1] == 'k'){
                return 1;
            }
            if (pos[king_y-1][king_x+1] == 'k'){
                return 1;
            }
            if (pos[king_y-1][king_x-1] == 'k'){
                return 1;
            }
        }
    else {
            if (pos[king_y+1][king_x] == 'K'){
                return 1;
            }
            if (pos[king_y][king_x+1] == 'K'){
                return 1;
            }
            if (pos[king_y-1][king_x] == 'K'){
                return 1;
            }
            if (pos[king_y][king_x-1] == 'K'){
                return 1;
            }
            if (pos[king_y+1][king_x+1] == 'K'){
                return 1;
            }
            if (pos[king_y+1][king_x-1] == 'K'){
                return 1;
            }
            if (pos[king_y-1][king_x+1] == 'K'){
                return 1;
            }
            if (pos[king_y-1][king_x-1] == 'K'){
                return 1;
            }
    }
    

    if (check_straight(pos, king_x, king_y, white, 1, 0)){
        return 1;
    }
    //printf("");
    if (check_straight(pos, king_x, king_y, white, -1, 0)){
        return 1;
    }
    //printf("\n");
    if (check_straight(pos, king_x, king_y, white, 0, 1)){
        return 1;
    }
    //printf("\n");
    if (check_straight(pos, king_x, king_y, white, 0, -1)){
        return 1;
    }

    if (check_diagonal(pos, king_x, king_y, white, 1,1)){
        return 1;
    }
    if (check_diagonal(pos, king_x, king_y, white, -1,1)){
        return 1;
    }
    if (check_diagonal(pos, king_x, king_y, white, 1,-1)){
        return 1;
    }
    if (check_diagonal(pos, king_x, king_y, white, -1,-1)){
        return 1;
    }

    if (check_knight(pos, king_x, king_y, white, 2, 1)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, -2, 1)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, 2, -1)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, -2, -1)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, 1, 2)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, 1, -2)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, -1, 2)){
        return 1;
    }
    if (check_knight(pos, king_x, king_y, white, -1, -2)){
        return 1;
    }


    return 0;

}

int check_straight(char pos[][8], int king_x, int king_y, int white, int vert, int hor){

    while (king_x >= 0 && king_y >= 0 && king_x <= 7 && king_y <= 7){
        king_x = king_x + hor;
        king_y = king_y + vert;
        if (king_x == 8 || king_y == 8 || king_x == -1 || king_y == -1){
            return 0;
        }
        if (white == 1){
            if (pos[king_y][king_x] == 'r' || pos[king_y][king_x] == 'q'){
                return 1;
            }
            else if (pos[king_y][king_x] != '.'){
                return 0;
            }
        }
        else{
            if (pos[king_y][king_x] == 'R' || pos[king_y][king_x] == 'Q'){
                return 1;
            }
            else if (pos[king_y][king_x] != '.'){
                return 0;
            }
        }
    }

    return 0;
}

int check_diagonal(char pos[][8], int king_x, int king_y, int white, int vert, int hor){
    
    while (king_x >= 0 && king_y >= 0 && king_x <= 7 && king_y <= 7){
        king_x = king_x+hor;
        king_y = king_y+vert;
        if (king_x == 8 || king_y == 8 || king_x == -1 || king_y == -1){
            return 0;
        }

        if (white == 1){
            if (pos[king_y][king_x] == 'b' || pos[king_y][king_x] == 'q'){
                return 1;
            }
            else if (pos[king_y][king_x] != '.'){
                return 0;
            }
        }
        else{
            if (pos[king_y][king_x] == 'B' || pos[king_y][king_x] == 'Q'){
                return 1;
            }
            else if (pos[king_y][king_x] != '.'){
                return 0;
            }
        }
    }

    return 0;
}

int check_knight(char pos[][8], int king_x, int king_y, int white, int vert, int hor){

    king_x = king_x + hor;
    king_y = king_y + vert;

    if (king_x >= 8 || king_y >= 8 || king_x <= -1 || king_y <= -1){
        return 0;
    }

    if (white == 1){
        if (pos[king_y][king_x] == 'n'){
            return 1;
        }
    }
    else {
        if (pos[king_y][king_x] == 'N'){
            return 1;
        }
    }

    return 0;

}