#include <stdio.h>
#include "board_print_plain.h"

void print_board(char board[][8])
{
    printf("   A B C D E F G H\n   _______________\n");
    for (int i = 0; i < 8; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < 8; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("   _______________\n   A B C D E F G H\n");
}