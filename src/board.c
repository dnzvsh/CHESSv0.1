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
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = ' ';
        }
    }
}

void parsing_white(Parsing* turn, int* start, int len)
{
    int count = 0;
    if (turn->data[*start] - 'a' >= 0) { //все фигуры с большой буквы, -> если
                                         //первая буква - маленькая - это пешка
        turn->white_figure = 'P';
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
            turn->white_turn[count] = turn->data[i] - '1';
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
            turn->black_turn[count] = turn->data[i] - '1';
            count++;
        }
    }
}

void swap(char* a, char* b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void cut(char* a, char* b)
{
    *b = *a;
    *a = ' ';
}

int check(Parsing* turn, char board[][8])
{
    for (int i = 0; i < 4; i++) {
        if (turn->white_turn[i] > 8) {
            printf("Invalid data\n");
            return -1;
        }
        if (turn->black_turn[i] > 8) {
            printf("Invalid data\n");
            return -1;
        }
    }
    if (turn->black_figure != board[turn->black_turn[1]][turn->black_turn[0]]) {
        printf("Invalid figure\n");
        return -1;
    }
    if (turn->white_figure != board[turn->white_turn[1]][turn->white_turn[0]]) {
        printf("Invalid figure\n");
        return -1;
    }
    if (turn->type_turn_black == 'x') {
        if (board[turn->black_turn[3]][turn->black_turn[2]] == ' '
            || islower(board[turn->black_turn[3]][turn->black_turn[2]])) {
            printf("Invalid target\n");
            return -1;
        }
    }
    if (turn->type_turn_white == 'x') {
        if (board[turn->white_turn[3]][turn->white_turn[2]] == ' '
            || isupper(board[turn->white_turn[3]][turn->white_turn[2]])) {
            printf("Invalid target\n");
            return -1;
        }
    }
    return 0;
}

int white_pawn(Parsing* turn, char board[][8])
{
    if (turn->type_turn_white == '-') {
        int max_turn = 1;
        if (turn->white_turn[1] == 1) {
            max_turn++;
        }
        if (turn->white_turn[0] != turn->white_turn[2]) {
            printf("white - Wrong coordinate\n");
            return -1;
        }
        if (turn->white_turn[3] - turn->white_turn[1] > max_turn
            || turn->white_turn[3] - turn->white_turn[1] <= 0) {
            printf("white - Invalid coordinate\n");
            return -1;
        }
        for (int i = turn->white_turn[1] + 1; i <= turn->white_turn[3]; i++) {
            if (board[i][turn->white_turn[2]] != ' ') {
                printf("white - Figure on the way\n");
                return -1;
            }
        }
        swap(&board[turn->white_turn[1]][turn->white_turn[0]],
             &board[turn->white_turn[3]][turn->white_turn[2]]);
        return 0;
    }
    if (turn->type_turn_white == 'x') {
        if (turn->white_turn[0] == turn->white_turn[2]) {
            printf("white - Wrong coordinate\n");
            return -1;
        }
        if (turn->white_turn[3] - turn->white_turn[1] > 1
            || turn->white_turn[3] - turn->white_turn[1] <= 0) {
            printf("white - Invalid coordinate\n");
            return -1;
        }
        if (turn->white_turn[2] - turn->white_turn[0] > 1
            || turn->white_turn[2] - turn->white_turn[0] < 1) {
            printf("while - invalid coordinate\n");
            return -1;
        }
        cut(&board[turn->white_turn[1]][turn->white_turn[0]],
            &board[turn->white_turn[3]][turn->white_turn[2]]);
        return 0;
    }
    printf("Invalid type turn\n");
    return -1;
}

int black_pawn(Parsing* turn, char board[][8])
{
    if (turn->type_turn_black == '-') {
        int max_turn = 1;
        if (turn->black_turn[1] == 6) {
            max_turn++;
        }
        if (turn->black_turn[0] != turn->black_turn[2]) {
            printf("black - Wrong coordinate\n");
            return -1;
        }
        if (turn->black_turn[3] - turn->black_turn[1] >= 0) {
            printf("black - Invalid coordinate\n");
            return -1;
        }
        for (int i = turn->black_turn[1] - 1; i >= turn->black_turn[3]; i--) {
            if (board[i][turn->black_turn[2]] != ' ') {
                printf("black - Figure on the way\n");
                return -1;
            }
        }
        swap(&board[turn->black_turn[1]][turn->black_turn[0]],
             &board[turn->black_turn[3]][turn->black_turn[2]]);
        return 0;
    }
    if (turn->type_turn_black == 'x') {
        if (turn->black_turn[0] == turn->black_turn[2]) {
            printf("black - Wrong coordinate\n");
            return -1;
        }
        if (turn->black_turn[1] - turn->black_turn[3] > 1
            || turn->black_turn[1] - turn->black_turn[3] <= 0) {
            printf("black - Invalid coordinate\n");
            return -1;
        }
        if (turn->black_turn[0] - turn->black_turn[2] > 1
            || turn->black_turn[0] - turn->black_turn[2] < 1) {
            printf("black - invalid coordinate\n");
            return -1;
        }
        cut(&board[turn->black_turn[1]][turn->black_turn[0]],
            &board[turn->black_turn[3]][turn->black_turn[2]]);
        return 0;
    }
    printf("Invalid type turn\n");
    return -1;
}

void input_data(Parsing* turn)
{
    turn->round++;
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
