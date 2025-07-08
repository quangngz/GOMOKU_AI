#include "functions.h"
#define MOVE_CURSOR_UP(n) for (int __i = 0; __i < (n); __i++) printf("\033[F\033[2K")
#define BOARD_DISPLAY_LINES (BOARD_ROW + 4)
#define STANDARD_DEPTH 5

int main(int argc, char *argv[]){
    int depth = STANDARD_DEPTH; 
    if (argc > 2 && argv[1]) {
        int input = atoi(argv[1]); 
        if (input && input <= 7) {
            depth = input; 
        }
    } 
    char player_col;
    bool X_turn = true;
    int player_row; 
    board_t board = {0ULL, 0ULL};
    printf("%ld\n", sizeof(board_t)); 

    printf("    GOMOKU, win in %d\n", WIN_CONDITION); 
    print_board(board); 
    printf("Player X enter your move in format COL ROW:"); 

    while (true) {
        if (win(board.X_pos)) {
            printf("Player X wins!\n");
            break;
        }
        if (win(board.O_pos)) {
            printf("Player O wins!\n");
            break;
        }
        uint64_t all_pieces = board.X_pos | board.O_pos;
        if (pop_count(all_pieces) == BOARDSIZE) {
            printf("It's a draw!\n");
            break;
        }
        if (X_turn) {
            printf("Player X enter move (COL ROW): ");
            if (scanf(" %c%d", &player_col, &player_row) != 2) {
                printf("Invalid input. Exiting.\n");
                // Keeps prompting for input until valid input appears
                int c; 
                while (((c = getchar()) != EOF && c != '\n')) {
                    continue; 
                }
            }

            int col = upper(player_col) - 'A';
            if (col < 0 || col >= BOARD_COL) {
                printf("Invalid column. Use A-%c.\n", 'A' + BOARD_COL - 1);
                continue;
            }
            if (player_row < 1 || player_row > BOARD_ROW) {
                printf("Invalid row. Use 1-%d.\n", BOARD_ROW);
                continue;
            }

            int pos = (player_row - 1) * BOARD_COL + col;
            if (!set_move(pos, &board.X_pos, board.O_pos)) {
                printf("Position Invalid!\n");
                continue; 
            }
            X_turn = false;
        } else {
            printf("Computer's thinking...\n"); 
            int best_move = find_best_move(board, depth);  // Depth 3 search
            if (best_move == -1) {
                printf("No valid moves available!\n"); 
                break; 
            }
            set_move(best_move, &board.O_pos, board.X_pos);
            int row = best_move / BOARD_COL + 1;
            char col = 'A' + (best_move % BOARD_COL);
            printf("Computer plays: %c%d\n", col, row);
            X_turn = true; 
        }

        MOVE_CURSOR_UP(BOARD_DISPLAY_LINES + 2);
        print_board(board);
        printf("Current turn: Player %c\n", X_turn ? 'X' : 'O');
    }
    return 0; 
        
}
