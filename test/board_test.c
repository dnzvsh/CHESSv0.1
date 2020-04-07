#include "board.h"
#include "board_print_plain.h"
#include "ctest.h"

// test pawns
//ходьба на 2 клетки
CTEST(test_pawns, pawn_turn_ok)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e2-e4 e7-e5");
    char board[8][8];
    initialize_board(board);
    turn->round++;
    // when
    int result = pawn_move(
            turn->round, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//ходьба на 3 клетки
CTEST(test_pawns, pawn_turn_error_move_to_3_cells)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e2-e5 a7-a4");
    char board[8][8];
    initialize_board(board);
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -5;
    ASSERT_EQUAL(expected, result);
}
//ходьба в бок
CTEST(test_pawns, pawn_turn_error_walking_in_the_side)
{
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e3-d3 e7-e5");
    char board[8][8];
    board[4][2] = 'P';
    initialize_board(board);
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -4;
    ASSERT_EQUAL(expected, result);
}
//ход по диагонали
CTEST(test_pawns, pawn_turn_error_walking_diagonally)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e2-d3 e7-d6");
    char board[8][8];
    initialize_board(board);
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -4;
    ASSERT_EQUAL(expected, result);
}
//ход пешки перед которой стоит фигура
CTEST(test_pawns, pawn_turn_error_walking_in_front_of_a_figure)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e2-e4 e7-e5");
    char board[8][8];
    initialize_board(board);
    board[2][4] = 'N';
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -7;
    ASSERT_EQUAL(expected, result);
}
//ход назад
CTEST(test_pawns, pawn_turn_error_move_back)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    parse_round(turn, "1. e3-e2 e7-e5");
    char board[8][8];
    initialize_board(board);
    board[4][1] = ' ';
    board[4][2] = 'P';
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -5;
    ASSERT_EQUAL(expected, result);
}
//правильная рубка (белые рубят черных)
CTEST(test_pawns, pawn_cut_ok)
{
    // given
    char board[8][8];
    initialize_board(board);
    Parsing a;
    Parsing* turn = &a;
    board[5][2] = 'n';
    parse_round(turn, "1. e2xf3 e7-e5");
    // when
    int result = pawn_move(
            turn->round + 1, turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//плохая рубка (белые рубят белых)
CTEST(test_pawns, pawn_cut_error_desertion)
{
    // given
    char board[8][8];
    initialize_board(board);
    Parsing a;
    Parsing* turn = &a;
    board[5][2] = 'N';
    parse_round(turn, "1. e2xf3 e7-e5");
    // when
    int result = turn_validation(
            turn->round + 1,
            turn->white_turn,
            turn->white_figure,
            turn->type_turn_white,
            board);
    // then
    int expected = -3;
    ASSERT_EQUAL(expected, result);
}
//рубка на место,где нет фигуры
CTEST(test_pawns, pawn_cut_error_cut_down_voids)
{
    // given
    char board[8][8];
    initialize_board(board);
    Parsing a;
    Parsing* turn = &a;
    board[5][2] = ' ';
    parse_round(turn, "1. e2xf3 e7-e5");
    // when
    int result = turn_validation(
            turn->round + 1,
            turn->white_turn,
            turn->white_figure,
            turn->type_turn_white,
            board);
    // then
    int expected = -3;
    ASSERT_EQUAL(expected, result);
}
//рубка фигуры назад
CTEST(test_pawns, pawn_cut_error_cutting_back)
{
    // given
    char board[8][8];
    int turn[] = {5, 2, 4, 1};
    initialize_board(board);
    board[5][2] = 'P';
    board[4][1] = 'n';
    int round = 1;
    char type_turn = 'x';
    // when
    int result = pawn_move(round, turn, type_turn, board);
    // then
    int expected = -5;
    ASSERT_EQUAL(expected, result);
}