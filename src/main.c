#include "board.h"
#include "board_print_plain.h"

int main()
{
    char board[8][8] = {{' '}};
    initiate_board(board);
    print_board(board);
    return 0;
}