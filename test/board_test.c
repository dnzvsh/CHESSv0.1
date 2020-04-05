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
//ход по диагонали
CTEST(test_pawns, pawn_turn_error04)
{
    // given
    int round = 1;
    int turn[] = {4, 1, 5, 2};
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
//ход пешки перед которой стоит фигура
CTEST(test_pawns, pawn_turn_error05)
{
    // given
    char board[8][8];
    int turn[] = {2, 1, 2, 2};
    initialize_board(board);
    board[2][2] = 'N';
    // when
    int result = turn_validation(1, turn, 'P', '-', board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//ход назад
CTEST(test_pawns, pawn_turn_error06)
{
    // given
    int round = 1;
    int turn[] = {4, 2, 4, 1};
    char board[8][8];
    initialize_board(board);
    board[4][1] = ' ';
    board[4][2] = 'P';
    int* turn_pawn = &turn[0];
    char type_turn = '-';
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//правильная рубка (белые рубят черных)
CTEST(test_pawns, pawn_cut_ok)
{
    // given
    char board[8][8];
    int turn[] = {4, 1, 5, 2};
    initialize_board(board);
    board[5][2] = 'n';
    int round = 1;
    char type_turn = 'x';
    int* turn_pawn = &turn[0];
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//плохая рубка (белые рубят белых)
CTEST(test_pawns, pawn_cut_error01)
{
    // given
    char board[8][8];
    int turn[] = {4, 1, 5, 2};
    initialize_board(board);
    board[5][2] = 'N';
    int* turn_pawn = &turn[0];
    // when
    int result = turn_validation(1, turn, 'P', 'x', board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//рубка на место,где нет фигуры
CTEST(test_pawns, pawn_cut_error02)
{
    // given
    char board[8][8];
    int turn[] = {4, 1, 5, 2};
    initialize_board(board);
    int* turn_pawn = &turn[0];
    // when
    int result = turn_validation(1, turn, 'P', 'x', board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}
//рубка фигуры назад
CTEST(test_pawns, pawn_cut_error03)
{
    // given
    char board[8][8];
    int turn[] = {5, 2, 4, 1};
    initialize_board(board);
    board[5][2] = 'P';
    board[4][1] = 'n';
    int round = 1;
    char type_turn = 'x';
    int* turn_pawn = &turn[0];
    // when
    int result = pawn_move(round, turn_pawn, type_turn, board);
    // then
    int expected = -1;
    ASSERT_EQUAL(expected, result);
}