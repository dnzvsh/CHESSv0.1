#include "board.h"
#include "board_print_plain.h"
#include "ctest.h"

// test pawns
//ходьба на 2 клетки
CTEST(test_pawns, pawn_turn_ok)
{
    // given
    int round = 1;
    int turn[] = {4, 1, 4, 3};
    int* turn_pawn = &turn[0];
    char type_turn = '-';
    char board[8][8];
    initialize_board(board);
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//ходьба на 3 клетки
CTEST(test_pawns, pawn_turn_error1)
{
    // given
    int round = 1;
    int turn[] = {4, 1, 4, 4};
    int* turn_pawn = &turn[0];
    char type_turn = '-';
    char board[8][8];
    initialize_board(board);
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//черные - ходьба на 3 клетки
CTEST(test_pawns, pawn_turn_error2)
{
    // given
    int round = 2;
    int turn[] = {4, 6, 4, 3};
    int* turn_pawn = &turn[0];
    char type_turn = '-';
    char board[8][8];
    initialize_board(board);
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//ходьба в бок
CTEST(test_pawns, pawn_turn_error03)
{
    // given
    int round = 1;
    int turn[] = {4, 1, 4, 3};
    int turn2[] = {4, 3, 3, 3};
    int* turn_pawn = &turn[0];
    char type_turn = '-';
    char board[8][8];
    initialize_board(board);
    pawn_move(round, turn_pawn, type_turn, board);
    turn_pawn = &turn2[0];
    pawn_move(round, turn_pawn, type_turn, board);
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}