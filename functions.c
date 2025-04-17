#include "functions.h"

#define BOARDSIZE 64
#define BOARD_COL 8 
#define BOARD_ROW 8 
#define WIN_CONDITION 4

typedef enum  {
    H = 0, G, F, E, D, C, B, A
} ROW;




int is_on(int value, board_t *board){
    return (((board->X_pos >> value) & 1) == 1) || (((board->O_pos >> value) & 1) == 1);
}
int is_X_on(int value, board_t *board){
    return (((board->X_pos >> value) & 1) == 1); 
}
int is_O_on(int value, board_t *board){
    return (((board->O_pos >> value) & 1) == 1); 
}

int win(int X_turn, board_t *board){

    // Check for verticals
    for (int col = 0; col < BOARD_COL; col++){
        for (int row = 0; row < BOARD_ROW - WIN_CONDITION; row++){
            int count = 0; 
            int pos = col + row * BOARD_COL; 
            for (int i = 0; i < WIN_CONDITION; i++){
                if (X_turn ? is_X_on(pos + i * BOARD_COL, board) : is_O_on(pos + i * BOARD_COL, board)) {
                    count++;
                }
                else {
                    break;
                }
            }
            if (count == WIN_CONDITION) {
                printf("%c wins on verticals!\n", X_turn ? 'X' : 'O'); 
                return 1; 
            }
        }
    }
    // Check for horizontals
    for (int row = 0; row < BOARD_ROW; row++){
        for (int col = 0; col <= BOARD_COL - WIN_CONDITION; col++){
            int pos = col + row * BOARD_COL; 
            int count = 0; 
            for (int i = 0; i < WIN_CONDITION; i++){
                if ((pos + i)/ BOARD_COL!= row) break;
                if (X_turn ? is_X_on(pos + i, board) : is_O_on(pos + i, board)) {
                    count++;
                } 
                else {
                    break;
                }
            }
            if (count == WIN_CONDITION){
                printf("%c win on horizontal!\n", X_turn ? 'X' : 'O');
                return 1; 
            }
        }
    }
    // Check for diagonals: bot right to top left 
    for (int col = 0; col < BOARD_COL - WIN_CONDITION; col++){
        for (int row = 0; row < BOARD_ROW - WIN_CONDITION; row++){
            int count = 0; 
            for (int i = 0; i < WIN_CONDITION; i++){
                int check_row = row + i;
                int check_col = col + i;
                int check_pos = check_col + check_row * BOARD_COL;
                if (check_col >= BOARD_COL || check_row >= BOARD_ROW) break;
                if (X_turn ? is_X_on(check_pos, board) : is_O_on(check_pos, board)){
                    count++;
                } 
                else {
                    break; 
                }
            }
            if (count == WIN_CONDITION) {
                printf("%c wins on diagonal!\n", X_turn ? 'X' : 'O');
                return 1; 
            }
        }
    }
    // Check for diagonals: Bot left to top right
    for (int row = 0; row < BOARD_ROW - WIN_CONDITION; row++) {
        for (int col = WIN_CONDITION - 1; col < BOARD_COL; col++){
            int count = 0; 
            for (int i = 0; i < WIN_CONDITION; i++){
                int check_row = row + i;
                int check_col = col - i;
                int check_pos = check_col + check_row * BOARD_COL;

                if (check_col < 0 || check_row >= BOARD_ROW) break;
                if (X_turn ? is_X_on(check_pos, board) : is_O_on(check_pos, board)){
                    count++; 
                } 
                else {
                    break; 
                }
            }
            if (count == WIN_CONDITION){
                printf("%c wins on diagonals!\n", X_turn ? 'X' : 'O'); 
                return 1;
            }
        }
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
int is_valid_move(int X_turn, int value, board_t *board){
    if (value > (BOARDSIZE - 1) || is_on(value, board)) {
        printf("Invalid position!\n");
        return 0; 
    }
    return 1; 
}
int set_move(int value, int X_turn, board_t *board){
    if (!is_valid_move(X_turn, value, board)) {
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