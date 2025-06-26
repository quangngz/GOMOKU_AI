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
    int X_turn = 1;
    int player_row;

    board_t *board = malloc(sizeof(board_t));
    if (!board) {
        perror("Memory allocation failed");
        fclose(fp);
        return 1;
    }

    board->X_pos = 0;
    board->O_pos = 0;

    while (!win(X_turn, board) && fscanf(fp, " %c%d", &player_col, &player_row) == 2) {
        int col = BOARD_COL - 1 - (upper(player_col) - 'A');
        int pos = (player_row - 1) * BOARD_COL + col;
        if (!set_move(pos, X_turn, board)) {
            continue;
        } else {
            if (win(X_turn, board)) {
                print_board(board);
                return 0;
            }
            X_turn = !X_turn;
        }
    }

    free(board);
    fclose(fp);
    return 0;
}
