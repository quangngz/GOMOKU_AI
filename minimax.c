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

// We use bit operators to find our consecutive patterns
/*       >>1      >>2      >>3
00011110 00001111 00011110 00111100
00000000 00000000 00000000 00000000
00000000 00000000 00000000 00000000 
00000000 00000000 00000000 00000000
If we take all of these and 
*/



int consecutive_fours(int64_t board, int row, int col) {
    for (int i )
    
}

double evaluate_position(board_t board, int X_turn){
    double my_score = 0; 
    double opponent_score = 0; 
    my_score += evaluate_line(X_pos, ROW, COL)
    /*TODO: WIN_CONDITION = 4
    Prioritize putting in spaces with little of opponents, and more of our own. 
    If open 4, basically is a win. open 3 and is your turn, also is a win. 
    half-open 4 is forcing, and hence is strong. 
    Creating double threats is strong.
    Try to search near the active zone, i.e. focus only up to the blank space at most 3 blocks away from 
    any marks.
    Score the opponent and subtract that into your position. 
    Make a heat map. 
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