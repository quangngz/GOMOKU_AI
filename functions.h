#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h> 

#define BOARDSIZE 64
#define BOARD_COL 8 
#define BOARD_ROW 8 
#define WIN_CONDITION 4
#define FULL_VALUE 0x7FFFFFFFFFFFFFFF
// Checks if bit number is set on the bit board
#define is_bit_on(bit, bitboard) (bitboard & (1ULL<<bit))

typedef struct {
    uint64_t X_pos; 
    uint64_t O_pos; 
} board_t; 
// Basic game functions
int win(uint64_t bitboard);

void print_board(board_t board);
bool set_move(int value, uint64_t *bitboard, uint64_t opponent);
char upper(char a);

int pop_count(uint64_t n);
bool is_on_board(int row, int col);
bool is_hot_move(board_t *board, int row, int col);
int make_move(board_t *board, int *moves);
void apply_move(uint64_t *bitboard, int pos);
void undo_move(uint64_t *bitboard, int pos);
char get_piece(board_t *board, int pos);
void extract_window(char *window, board_t *board, int row, int col, int dir, bool *is_valid_window);
double evaluate_window(char *window);
double evaluate_position(board_t *board);
double minimax(board_t *board, int depth, bool X_turn, int *best_move);
int find_best_move(board_t board, int depth);