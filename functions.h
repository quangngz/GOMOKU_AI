#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#define FULL_VALUE 0x7FFFFFFFFFFFFFFFULL
typedef struct {
    uint64_t X_pos; 
    uint64_t O_pos; 
} board_t; 
// Board functions - basic game functions
int is_on(int value, board_t *board);
int is_X_on(int value, board_t *board);
int is_O_on(int value, board_t *board);
int win(int X_turn, board_t *board);
int is_valid_move(int X_turn, int value, board_t *board); 

void print_board(board_t *board);
int set_move(int value, int X_turn, board_t *board);
char upper(char a);

// Minimax's functions
/*The node datastructure doesn't need a parent because it can back track inside the call stack. */
typedef struct node_t{
    int value; 
    struct node_t **children; 
    int n_children; 
} node_t; 
node_t* create_node(int value);
void add_child(node_t* parent, node_t* child);
node_t* get_children(node_t current);
void free_node(node_t* node); 
int evaluate_position(int64_t board, int X_turn); 
node_t** generate_children(node_t* current_state, int* child_count);



int minimax(node_t node, int depth, int is_maximizing);