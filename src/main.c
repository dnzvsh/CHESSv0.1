#include "board.h"
#include "board_print_plain.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int t = 0;
    char board[8][8] = {{' '}};
    Parsing* turn = malloc(sizeof(Parsing));
    turn->round = 0;
    initiate_board(board);
    print_board(board);
    for (int j = 0; j < 5950; j++) { // 5950 - максимум ходов по правилам шахмат
        input_data(turn);
        t = check(turn, board);
        if (t) {
            return 0;
        }
        switch (turn->white_figure) {
        case 'P':
            t = white_pawn(turn, board);
            break;
        default:
            t = -1;
        }
        print_board(board);
        if (t) {
            return 0;
        }
        switch (turn->black_figure) {
        case 'p':
            t = black_pawn(turn, board);
            break;
        default:
            t = -1;
        }
        print_board(board);
        if (t) {
            return 0;
        }
    }
    return 0;
}