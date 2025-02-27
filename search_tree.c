#include <stdio.h>
#include <stdlib.h>
#include "moves.c"

struct copy start;

int search_depth(char pos[][8], int depth){

    if (depth == 0){
        copy_stats(&start);
    }

    while (depth != 3){
        search_depth(pos, depth+1);
    }


}