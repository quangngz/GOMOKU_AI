#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define BOARDSIZE 64
#define BOARD_COL 8 
#define BOARD_ROW 8 
#define WIN_CONDITION 4


typedef struct {
    uint64_t X_pos; 
    uint64_t O_pos; 
} board_t; 
// Basic game functions
int is_on(int value, board_t *board);
int is_X_on(int value, board_t *board);
int is_O_on(int value, board_t *board);
int win(int X_turn, board_t *board);
int is_valid_move(int value, board_t *board); 

void print_board(board_t *board);
int set_move(int value, int X_turn, board_t *board);
char upper(char a);

// Minimax's functions
/*The node datastructure doesn't need a parent because it can back track inside the call stack. */
typedef struct node_t{
    int value; 
    struct node_t **children; 
    int n_children; 
    int64_t current_board; 
    int X_turn; 
} node_t; 
node_t* create_node(int value);
void add_child(node_t* parent, node_t* child);
node_t* get_children(node_t current);
void free_node(node_t* node); 
int evaluate_position(int64_t board, int X_turn); // The outer function. 
node_t** generate_children(node_t* current_state, int* child_count);



int minimax(node_t node, int depth, int is_maximizing);