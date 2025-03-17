int check_diag(char pos[][8], int cur_x, int cur_y, int dest_x, int dest_y);
struct stats {
    int en_p;
    int en_p_y;
    int unMovW_k;
    int unMovB_k;
    int unMovW_RL;
    int unMovW_RR;
    int unMovB_RL;
    int unMovB_RR;
    int counter;
};
void copy_stats(struct stats *dest, struct stats curr);
int piece(char pos[][8], int cur_x, int cur_y , int dest_x, int dest_y, struct stats *game_stats);