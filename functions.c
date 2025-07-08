#include "functions.h"


static inline int is_consecutive(uint64_t pos, int shift) {
    return (pos & (pos >> shift) & (pos >> (2 * shift)) & (pos >> (3 * shift))) != 0;
}

int win(uint64_t bitboard) {
    // Horizontal check
    if (is_consecutive(bitboard, 1)) {
        return true; 
    }
    // Vertical check
    if (is_consecutive(bitboard, BOARD_ROW)) {
        return true; 
    }
    // Diagonal: top left to bot right
    if (is_consecutive(bitboard, BOARD_ROW + 1)) {
        return true; 
    }
    // Diagonal: top right to bot left
    if (is_consecutive(bitboard, BOARD_ROW - 1)) {
        return true; 
    }
    return false; 
}

void print_board(board_t board) {
    printf("    A  B  C  D  E  F  G  H\n");
    for (int row = BOARD_ROW - 1; row >= 0; row--) {
        printf("%2d ", row + 1);
        for (int col = 0; col < BOARD_COL; col++) {
            int pos = row * BOARD_COL + col;
            if (is_bit_on(pos, board.X_pos)) {
                printf(" X ");
            } else if (is_bit_on(pos, board.O_pos)) {
                printf(" O ");
            } else {
                printf(" _ ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

// Return true if success. 
bool set_move(int value, uint64_t *bitboard, uint64_t opponent){
    if (value >= BOARDSIZE || is_bit_on(value, *bitboard) || is_bit_on(value, opponent)) {
        return false; 
    }
    *bitboard = *bitboard | (1ULL << value); 
    return true; 
}

char upper(char a){
    if (islower(a)){
        a += 'A' - 'a';
    }
    return a; 
}