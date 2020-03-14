#include "board.h"
#include "board_print_plain.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    char board[8][8] = {{' '}};
    Parsing* turn = malloc(sizeof(Parsing));
    initiate_board(board);
    print_board(board);
    input_data(turn);
    printf("White:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", turn->white_turn[i]);
    }
    printf("\nBlack:\n");
    for (int i = 0; i < 4; i++) {
        printf("%d ", turn->black_turn[i]);
    }
    printf("\nblack = %c, white = %c\n",
           turn->black_figure,
           turn->white_figure);
    printf("Black_type = %c\nWhite type = %c\n",
           turn->type_turn_black,
           turn->type_turn_white);
    return 0;
}