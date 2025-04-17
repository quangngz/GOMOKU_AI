#include "functions.h"

node_t* create_node(int value){
    node_t *new_node = (node_t*)malloc(sizeof(node_t));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation error"); 
        exit(EXIT_FAILURE); 
    }
    new_node->value = value; 
    new_node->children = NULL; 
    new_node->n_children = 0; 
    return new_node; 
}
void add_child(node_t* parent, node_t* child){
    // Children array is dynamic
    parent->n_children++; 
    parent->children = (node_t**)realloc(parent->children, parent->n_children * sizeof(node_t)); 
    if (parent->n_children > 0 && parent->children == NULL){
        fprintf(stderr, "Memory allocation error"); 
        exit(EXIT_FAILURE); 
    }
    parent->children[parent->n_children - 1] = child; 
}

node_t* get_children(node_t* parent, int* count){
    // Return the children list, as well as setting a list length for modifications
    if (parent == NULL){
        *count = 0;
        return NULL; 
    }
    *count = parent->n_children; 
    return parent->n_children;
}
void free_node(node_t* node) {
    /*If there's nothing, then we don't do anything. Else move until we are at the bottom chidren
    which doesn't have children. Free those node, then back track and free 
    the array that used to store them. Then free the parent node*/
    if (node == NULL) return; 
    for (int i = 0; i < node->n_children; i++){
        free_node(node->children[i]); 
    }
    if (node->children != NULL) {
        free(node->children); 
    }
    free(node); 
}

int evaluate_position(uint64_t board, int X_turn){
    if (board == FULL_VALUE) return 0; // So its a tie. 
    if (X_turn && win(1, board)) return 10; // X wins
    if (!X_turn && win(0, board)) return -10; // O wins

    /*Strategy is: higher score if a piece is in the middle with unblocked ends 
    if two consecutive pieces with unblocked ends, then a higher score. 
    if WINCONDITION - 1 consecutive pieces with unblocked ends and opponent doesn't have it, then win. 
    strategy for attacking is to make the most consecutive pieces with unblocked ends.
    strategy for defending is to block most .
    */ 



}


node_t** generate_children(node_t* current_state, int* child_count) {
    /* 1st step: find all empty cells
    2nd step: find valid moves.
    3rd step: for each move, make a node. 
    - calculate the value of the board state at that node. then create_node(value)
    4th step: put the nodes inside the array. 
    */
}