#include "functions.h"
static inline int is_consecutive(uint64_t pos, int shift) {
    return (pos & (pos >> shift) & (pos >> (2 * shift)) & (pos >> (3 * shift))) != 0;
}


int is_on(int value, board_t *board){
    return (((board->X_pos >> value) & 1) == 1) || (((board->O_pos >> value) & 1) == 1);
}
int is_X_on(int value, board_t *board){
    return (((board->X_pos >> value) & 1) == 1); 
}
int is_O_on(int value, board_t *board){
    return (((board->O_pos >> value) & 1) == 1); 
}

int win(int X_turn, board_t *board) {
    // Horizontal check
    if (X_turn && is_consecutive(board->X_pos, 1)) {
        printf("X wins on horizontals!\n"); 
        return 1; 
    }
    if (!X_turn && is_consecutive(board->X_pos, 1)) {
        printf("O wins on horizontals!\n"); 
        return 1; 
    }
    // Vertical check
    if (X_turn && is_consecutive(board->X_pos, BOARD_ROW)) {
        printf("X wins on verticals!\n"); 
        return 1; 
    }
    if (!X_turn && is_consecutive(board->X_pos, BOARD_ROW)) {
        printf("O wins on verticals!\n"); 
        return 1; 
    }
    // Diagonal: top left to bot right
    if (X_turn && is_consecutive(board->X_pos, BOARD_ROW + 1)) {
        printf("X wins on top-left to bottom-right diagonals!\n"); 
        return 1; 
    }
    if (!X_turn && is_consecutive(board->X_pos, BOARD_ROW + 1)) {
        printf("O wins on top-left to bottom-right diagonals!\n"); 
        return 1; 
    }
    // Diagonal: top right to bot left
    if (X_turn && is_consecutive(board->X_pos, BOARD_ROW - 1)) {
        printf("X wins on top-right to bottom-left diagonals!\n"); 
        return 1; 
    }
    if (!X_turn && is_consecutive(board->X_pos, BOARD_ROW - 1)) {
        printf("O wins on top-right to bottom-left diagonals!\n"); 
        return 1; 
    }
    return 0; 
}

void print_board(board_t *board){
    printf("    A  B  C  D  E  F  G  H");
    for (int i = BOARDSIZE - 1; i >= 0; i--){
        if (i % BOARD_ROW == BOARD_ROW - 1) {
            printf("\n"); 
            printf("%2d ", i / BOARD_ROW + 1); 
        }
        if (is_X_on(i, board)){
            printf(" X ");
        } else if (is_O_on(i, board)) {
            printf(" O ");
        } else {
            printf(" _ ");
        }
    }
    printf("\n");
}
int is_valid_move(int value, board_t *board){
    if (value > (BOARDSIZE - 1) || is_on(value, board)) {
        printf("Invalid position!\n");
        return 0; 
    }
    return 1; 
}
int set_move(int value, int X_turn, board_t *board){
    if (!is_valid_move(value, board)) {
        return 0; 
    }
    if (X_turn) {
        board->X_pos = board->X_pos | (1ULL << value); 
        return 1; 
    }
    else {
        board->O_pos = board->O_pos | (1ULL << value);
        return 1; 
    }
}

char upper(char a){
    if (islower(a)){
        a += 'A' - 'a';
    }
    return a; 
}