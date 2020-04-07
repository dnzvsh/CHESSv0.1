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
CTEST(test_pawns, pawn_cut_error_down_voids)
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

// tests rook
//Ходьба по вертикали
CTEST(test_rooks, rook_walking_vertically)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][1] = 'R';
    parse_round(turn, "1. Ra2-a5 e7-e5");
    // when
    int result = rook_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//Ходьба в бок
CTEST(test_rooks, rook_walking_in_the_side)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][2] = 'R';
    parse_round(turn, "1. Ra3-e3 e7-e5");
    // when
    int result = rook_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//Ходьба если перед ладьей фигура
CTEST(test_rooks, rook_error_walking_in_front_of_a_figure)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    parse_round(turn, "1. Ra1-a5 e7-e5");
    // when
    int result = rook_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -11;
    ASSERT_EQUAL(expected, result);
}
//Ходьба ладьи по диагонали
CTEST(test_rooks, rook_error_walking_diagonally)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][2] = 'R';
    parse_round(turn, "1. Ra3-e6 e7-e5");
    // when
    int result = rook_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -10;
    ASSERT_EQUAL(expected, result);
}
//Правильная рубка
CTEST(test_rooks, rook_cut_ok)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][2] = 'R';
    parse_round(turn, "1. Ra3xa7 e7-e5");
    // when
    int result = rook_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//рубка своих
CTEST(test_rooks, rook_cut_error_desertion)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    parse_round(turn, "1. Ra1xa2 e7-e5");
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
//рубка там, где пустое место
CTEST(test_rooks, rook_cut_error_down_voids)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][1] = ' ';
    parse_round(turn, "1. Ra1xa2 e7-e5");
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
// tests Knight
//Правильный ход
CTEST(test_knight, knight_turn_ok)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    parse_round(turn, "1. Nb1-a3 e7-e5");
    // when
    int result = knight_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}
//ход по вертикали
CTEST(test_knight, knight_turn_error_walking_vertically)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    parse_round(turn, "1. Nb1-b3 e7-e5");
    // when
    int result = knight_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -9;
    ASSERT_EQUAL(expected, result);
}
//ход в бок
CTEST(test_knight, knight_turn_error_walking_in_the_side)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[1][2] = 'N';
    parse_round(turn, "1. Nb3-e3 e7-e5");
    // when
    int result = knight_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -9;
    ASSERT_EQUAL(expected, result);
}
//ход по диагонали
CTEST(test_knight, knight_turn_error_walking_diagonally)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[1][2] = 'N';
    parse_round(turn, "1. Nb3-e6 e7-e5");
    // when
    int result = knight_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = -9;
    ASSERT_EQUAL(expected, result);
}
//правильная рубка
CTEST(test_knight, knight_cut_ok)
{
    // given
    Parsing a;
    Parsing* turn = &a;
    char board[8][8];
    initialize_board(board);
    board[0][2] = 'n';
    parse_round(turn, "1. Nb1xa3 e7-e5");
    // when
    int result = knight_move(turn->white_turn, turn->type_turn_white, board);
    // then
    int expected = 0;
    ASSERT_EQUAL(expected, result);
}

