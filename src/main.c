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
        for (int i = 0; i < 2; i++) {
            correct = turn_figure(turn, board);
            if (correct) {
                printf("Invalid turn\n");
                return 0;
            }
            print_board(board);
        }
    }
    return 0;
}