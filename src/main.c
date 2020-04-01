#include "board.h"
#include "board_print_plain.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    const int max_turn = 5950; //максимум ходов по правилам шахмат
    int uncorrect = 0;
    char board[8][8] = {{' '}};
    Parsing t;
    Parsing* turn = &t;
    turn->round = 0;
    initialize_board(board);
    print_board(board);
    for (int j = 0; j < max_turn; j++) {
        input_data(turn);
        uncorrect = turn_figure(
                &turn->round,
                turn->white_turn,
                turn->white_figure,
                turn->type_turn_white,
                board);
        print_board(board);
        if (uncorrect) {
            printf("Invalid turn\n");
            return 0;
        }
        uncorrect = turn_figure(
                &turn->round,
                turn->black_turn,
                turn->black_figure,
                turn->type_turn_black,
                board);
        print_board(board);
        if (uncorrect) {
            printf("Invalid turn\n");
            return 0;
        }
    }
    return 0;
}