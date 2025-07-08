#include "functions.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("Failed to open input file");
        return 1;
    }

    char player_col;
    bool X_turn = true;
    int player_row; 
    board_t board = {0ULL, 0ULL};         
    while (!win(X_turn, board.X_pos) && !win(!X_turn, board.O_pos) && fscanf(fp, " %c%d", &player_col, &player_row) == 2){
        int col = BOARD_COL - 1 - (upper(player_col) - 'A');
        int pos = (player_row - 1) * BOARD_COL + col;

        if (X_turn) {
            if (!set_move(pos, &board.X_pos, board.O_pos)) {
            } else {
                if (win(X_turn,board.X_pos)) return 0; 
                X_turn = !X_turn; 
            }
        }
        else {
            if (!set_move(pos, &board.O_pos, board.X_pos)) {
            } else {
                if (win(X_turn,board.O_pos)) return 0; 
                X_turn = !X_turn; 
            }
        }
    }
    print_board(board);
    fclose(fp);
    return 0;
}




