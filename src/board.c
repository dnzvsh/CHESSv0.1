#include "board.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void initiate_board(char board[][8])
{
    board[7][1] = 'n';
    board[7][2] = 'b';
    board[7][3] = 'k';
    board[7][4] = 'q';
    board[7][5] = 'b';
    board[7][6] = 'n';
    board[7][7] = 'r';
    board[7][0] = 'r';
    for (int i = 0; i < 8; i++) {
        board[6][i] = 'p';
        board[1][i] = 'P';
    }
    board[0][0] = 'R';
    board[0][1] = 'N';
    board[0][2] = 'B';
    board[0][3] = 'Q';
    board[0][4] = 'K';
    board[0][5] = 'B';
    board[0][6] = 'N';
    board[0][7] = 'R';
}

void parsing_white(Parsing* turn, int* start, int len)
{
    int count = 0;
    if (turn->data[*start] - 'a' >= 0) { //все фигуры с большой буквы, -> если
                                         //первая буква - маленькая - это пешка
        turn->white_figure = 'p';
        turn->white_turn[0] = turn->data[*start] - 'a';
        count++;
    } else {
        turn->white_figure = turn->data[*start];
    }

    for (int i = *start + 1; i < len; i++) {
        if (turn->data[i] == ' ') { // eсли смена хода, выходим из цикла
            *start = i;
            break;
        }
        if (turn->data[i] == 'x'
            || turn->data[i] == '-') { //если тип хода, то записываем его и на
                                       //следующую итерацию
            turn->type_turn_white = turn->data[i];
            continue;
        }

        if (isalpha(turn->data[i])) {
            turn->white_turn[count] = turn->data[i] - 'a';
            count++;
        }

        if (isdigit(turn->data[i])) {
            turn->white_turn[count] = turn->data[i] - '0';
            count++;
        }
    }
}

void parsing_black(Parsing* turn, int* start, int len)
{
    int count = 0;
    if (turn->data[*start] - 'a' >= 0) { //все фигуры с большой буквы, -> если
                                         //первая буква - маленькая - это пешка
        turn->black_figure = 'p';
        turn->black_turn[0] = turn->data[*start] - 'a';
        count++;

    } else {
        turn->black_figure = turn->data[*start];
    }

    for (int i = *start + 1; i <= len; i++) {
        if (turn->data[i] == 'x' || turn->data[i] == '-') {
            turn->type_turn_black = turn->data[i];
            continue;
        }

        if (isalpha(turn->data[i])) {
            turn->black_turn[count] = turn->data[i] - 'a';
            count++;
        }

        if (isdigit(turn->data[i])) {
            turn->black_turn[count] = turn->data[i] - '0';
            count++;
        }
    }
}

void input_data(Parsing* turn)
{
    char i = getchar();
    int len = 1;
    turn->data[0] = i;
    while (i != '\n') {
        i = getchar();
        turn->data[len] = i;
        len++;
    }
    int count = 0;
    parsing_white(turn, &count, len);
    count++;
    parsing_black(turn, &count, len);
}