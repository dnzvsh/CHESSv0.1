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
        correct = turn_validation(turn, board);
        if (correct) {
            return 0;
        }
        switch (turn->white_figure) {
        case 'P':
            correct = pawn_move(turn, board);
            break;
        case 'N':
            correct = knight_move(turn, board);
            break;
        case 'R':
            correct = rook_move(turn, board);
            break;
        case 'B':
            correct = bishop_move(turn, board);
            break;
        case 'Q':
            correct = queen_move(turn, board);
            break;
        case 'K':
            correct = king_move(turn, board);
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
        correct = turn_validation(turn, board);
        if (correct) {
            return 0;
        }
        switch (turn->black_figure) {
        case 'p':
            correct = pawn_move(turn, board);
            break;
        case 'n':
            correct = knight_move(turn, board);
            break;
        case 'r':
            correct = rook_move(turn, board);
            break;
        case 'b':
            correct = bishop_move(turn, board);
            break;
        case 'q':
            correct = queen_move(turn, board);
            break;
        case 'k':
            correct = king_move(turn, board);
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