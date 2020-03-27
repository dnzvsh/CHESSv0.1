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
        turn->round++;
        correct = data_validation(turn, board);
        if (correct) {
            return 0;
        }
        switch (turn->white_figure) {
        case 'P':
            if (turn->type_turn_white == '-') {
                correct = pawn_move(turn, board);
                break;
            }
            correct = pawn_cut(turn, board);
            break;
        case 'N':
            correct = knight_move(turn, board);
            break;
            break;
        default:

            correct = -1;
        }
        print_board(board);
        if (correct) {
            printf("Invalid white turn\n");
            return 0;
        }
        turn->round++;
        correct = data_validation(turn, board);
        if (correct) {
            return 0;
        }
        switch (turn->black_figure) {
        case 'p':
            if (turn->type_turn_black == '-') {
                correct = pawn_move(turn, board);
                break;
            }
            correct = pawn_cut(turn, board);
            break;
        case 'n':
            correct = knight_move(turn, board);
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