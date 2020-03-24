#include "board.h"
#include "board_print_plain.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int max_turn = 5950; //максимум ходов по правилам шахмат
    int correct = 0;
    char board[8][8] = {{' '}};
    Parsing t;
    Parsing* turn = &t;
    turn->round = 0;
    initialize_board(board);
    print_board(board);
    for (int j = 0; j < max_turn; j++) {
        input_data(turn);
        correct = data_validation(turn, board);
        if (correct) {
            return 0;
        }
        switch (turn->white_figure) {
        case 'P':
            correct = white_pawn_move(turn, board);
            break;
        case 'N':
            correct = white_knight_move(turn, board);
            break;
        default:
            correct = -1;
        }
        print_board(board);
        if (correct) {
            printf("Invalid white turn\n");
            return 0;
        }
        switch (turn->black_figure) {
        case 'p':
            correct = black_pawn_move(turn, board);
            break;
        case 'n':
            correct = black_knight_move(turn, board);
            break;
        default:
            correct = -1;
        }
        print_board(board);
        if (correct) {
            printf("Invalid black turn\n");
            return 0;
        }
    }
    return 0;
}