#include "functions.h"
#define INVALID 'I'
#define WINDOW_SIZE WIN_CONDITION
const uint8_t direction[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}}; 
static int run_scores[] = {50, 100, 200}; 


int pop_count(uint64_t n) {
    int c = 0;
    for (; n; ++c)
        n &= n - 1;
    return c;
}

bool is_on_board(int row, int col) {
    return (0 <= row && row < BOARD_ROW) && (0 <= col && col < BOARD_COL);
}

/* To somewhat reduce the insertion of unneccesary moves
LOGIC: For a given position, evaluate in 4 directions to see if there's 
any active nodes nearby*/ 
bool is_hot_move(board_t *board, int row, int col) {
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < WIN_CONDITION; j++) {
            int curr_row = row + direction[i][0] * j; 
            int curr_col = col + direction[i][1] * j; 
            int curr_pos = curr_row * BOARD_COL + curr_col; 
            if (is_on_board(curr_row, curr_col) && 
                (is_bit_on(curr_pos, board->X_pos) || is_bit_on(curr_pos, board->O_pos))) {
                return true; 
            }
        }
    }
    return false; 
}

// This function is called alot, so pass by reference is better
int make_move(board_t *board, int *moves) {
    int move_count = 0; 
    int center = (BOARD_ROW / 2) * BOARD_COL + (BOARD_COL / 2); 
    if (!is_bit_on(center, board->X_pos) && 
        !is_bit_on(center, board->O_pos)) {
        moves[move_count++] = center; // Play in center
    }

    for (int row = 0; row < BOARD_ROW; row++) {
        for (int col = 0; col < BOARD_COL; col++) {
            int pos = row * BOARD_COL + col; 
            if (is_bit_on(pos, board->X_pos) || is_bit_on(pos, board->O_pos)) {
                continue; 
            }   
            if (pos != center && is_hot_move(board, row, col)) {
                moves[move_count++] = pos; 
            }
        }
    }
    return move_count; 
}

void apply_move(uint64_t *bitboard, int pos) {
    *bitboard = *bitboard | (1ULL << pos); 
}
void undo_move(uint64_t *bitboard, int pos) {
    *bitboard = *bitboard & ~(1ULL << pos); 
}
// I O X X _ O 
char get_piece(board_t *board, int pos) {
    if (pos < 0 || pos >= BOARDSIZE) {
        return INVALID; 
    }
    if (is_bit_on(pos, board->X_pos)) {
        return 'X'; 
    } 
    if (is_bit_on(pos, board->O_pos)) {
        return 'O'; 
    }
    return ' '; 
}
void extract_window(char *window, board_t *board, int row, int col, int dir, bool *is_valid_window) {
    *is_valid_window = true; 
    int curr_row; int curr_col;
    for (int i = 0; i < WINDOW_SIZE; i++) {
        curr_row = row + direction[dir][0] * i; 
        curr_col = col + direction[dir][1] * i;
        if (is_on_board(curr_row, curr_col)) {
            window[i] = get_piece(board, curr_row * BOARD_COL + curr_col);
        } else {
            window[i] = INVALID; 
            *is_valid_window = false; 
            return; 
        }
    }
}

double evaluate_window(char *window){
    // Find consecutive streaks without obstacles. 
    // Has to have enough space for WIN CONDITION
    int n_empty = 0; int O_pieces = 0; int X_pieces = 0; 
    int max_X_run = 0; int max_O_run = 0; 
    int current_X_run = 0; int current_O_run = 0; 

    for (int i = 0; i < WINDOW_SIZE; i++) {
        if (window[i] == 'O') {
            O_pieces++; 
            current_O_run++; 
            if (current_O_run > max_O_run) max_O_run = current_O_run; 
            current_X_run = 0; 
        } else if (window[i] == 'X') {
            X_pieces++; 
            current_X_run++; 
            if (current_X_run > max_X_run) max_X_run = current_X_run; 
            current_O_run = 0; 
        } 
        else if (window[i] == ' ') {
            n_empty++; 
            current_O_run = 0; 
            current_X_run = 0; 
        }
    }
    if (max_O_run >= WIN_CONDITION) return 1000; 
    if (max_X_run >= WIN_CONDITION) return -1000; 

    //Evaluate based on dominance
    if (O_pieces > 0 && X_pieces > 0) {
        // Favor the player with better streak
        double streak_score = run_scores[max_O_run] - run_scores[max_X_run];
        // Add small bonus for piece count advantage
        double piece_advantage = (O_pieces - X_pieces) * 2;
        return streak_score + piece_advantage;
    }

    double score = 0; 
    // Pure O window
    if (O_pieces > 0 && X_pieces == 0) {
        score += run_scores[max_O_run];
        score += O_pieces * 10;
        if (O_pieces + n_empty >= WIN_CONDITION) {
            score += n_empty * 5;  
            if (O_pieces == WIN_CONDITION - 1 && n_empty >= 1) {
                score += 200;  
            }
            if (O_pieces == WIN_CONDITION - 2 && n_empty >= 2) {
                score += 100; 
            }
        }
    }
    // Pure X window
    if (X_pieces > 0 && O_pieces == 0) {
        score -= run_scores[max_X_run];
        score -= X_pieces * 10;
        if (X_pieces + n_empty >= WIN_CONDITION) {
            score -= n_empty * 5;
            if (X_pieces == WIN_CONDITION - 1 && n_empty >= 1) {
                score -= 200;  
            }
            if (X_pieces == WIN_CONDITION - 2 && n_empty >= 2) {
                score -= 100; 
            }
        }
    }
    
    return score;
}
// This function is called alot...
double evaluate_position(board_t *board){
    double score = 0; 
    uint64_t all_pieces = board->X_pos | board->O_pos; 
    if (pop_count(all_pieces) == BOARD_COL * BOARD_ROW) {
        return 0; 
    }
    for (int row = 0; row < BOARD_ROW; row++) {
        for (int col = 0; col < BOARD_COL; col++) {
            if (is_hot_move(board, row, col)) {
                // dir is direction index
                for (int dir = 0; dir < 4; dir++) {
                    bool is_valid_window = true; 
                    char window[WINDOW_SIZE]; 
                    extract_window(window, board, row, col, dir, &is_valid_window);
                    if (is_valid_window) {
                         score += evaluate_window(window); 
                    } 
                }
            }
        }   
    }
    return score; 
}


/* Minimise for X, maximise for O*/
double minimax(board_t *board, int depth, bool X_turn, int *best_move) {
    if (win(board->X_pos)) return -1000;
    if (win(board->O_pos)) return 1000;
    if (depth == 0) {
        return evaluate_position(board); 
    } 
    int moves[BOARD_COL * BOARD_ROW]; 
    int move_count = make_move(board, moves);  
    if (X_turn) {
        double min_eval = INFINITY; 
        int local_best = moves[0]; 

        for (int i = 0; i < move_count; i++) {
            apply_move(&board->X_pos, moves[i]); 
            double eval = minimax(board, depth - 1, false, NULL); 
            undo_move(&board->X_pos, moves[i]);
            if (eval < min_eval) {
                min_eval = eval; 
                local_best = moves[i]; 
            }
        }
        if (best_move) *best_move = local_best; 
        return min_eval;

    }
    // Maximise for this
    else if (!X_turn) {
        double max_eval = -INFINITY; 
        int local_best = moves[0]; 
        for (int i = 0; i < move_count; i++) {
            apply_move(&board->O_pos, moves[i]); 
            double eval = minimax(board, depth - 1, true, NULL); 
            undo_move(&board->O_pos, moves[i]);
            if (eval > max_eval) {
                max_eval = eval; 
                local_best = moves[i]; 
            }
        }
        if (best_move) *best_move = local_best; 
        return max_eval;
    }
    return 0; // Just to avoid warnings
}


int find_best_move(board_t board, int depth) {
    int best_move = -1; 
    minimax(&board, depth, false, &best_move);
    return best_move; 
}
