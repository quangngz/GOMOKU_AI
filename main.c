#include "functions.h"
#define MOVE_CURSOR_UP(n) for (int __i = 0; __i < (n); __i++) printf("\033[F\033[2K")
#define BOARD_DISPLAY_LINES 10

int main(int argc, char *argv[]){
    char player_col;
    int X_turn = 1;
    int player_row; 
    board_t *board = malloc(sizeof(board_t));
    printf("%ld\n", sizeof(board_t)); 
    board->X_pos = 0;
    board->O_pos = 0;

    printf("    GOMOKU, win in %d\n", WIN_CONDITION); 
    print_board(board); 
    printf("Player X enter your move in format COL ROW:"); 

    while (!win(X_turn, board) && scanf(" %c%d", &player_col, &player_row) == 2){
        int col = BOARD_COL - 1 - (upper(player_col) - 'A');
        int pos = (player_row - 1) * BOARD_COL + col;
        if (!set_move(pos, X_turn, board )){
            // If this is reached, it means player enter invalid positions
            MOVE_CURSOR_UP(1); 
            if (X_turn) {
                printf("Player X enter your move in format COL ROW:"); 
            } else {
                printf("Player O enter your move in format COL ROW:"); 
            }
        }
        else {
            MOVE_CURSOR_UP(BOARD_DISPLAY_LINES);
            print_board(board);
            if (win(X_turn,board)) return 0; 
            X_turn = !X_turn; 
            if (X_turn) {
                printf("Player X enter your move in format COL ROW:"); 
            } else {
                printf("Player O enter your move in format COL ROW:"); 
            }
        }
    }
    free(board);
    return 0; 
}





