#include "board.h"
#include "board_print_plain.h"
#include "ctest.h"

// test pawns
CTEST(test_pawns, pawn_turn)
{
    // given
    const int round = 1;
    const int turn[] = {4, 1, 4, 3};
    const int* turn_pawn = &turn;
    const char type_turn = '-';
    char board[8][8];
    initialize_board(board);
    // when
    const result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    const int expected = 0;
    ASSERT_EQUAL(expected, result);
}