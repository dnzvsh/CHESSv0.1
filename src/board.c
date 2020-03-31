#include "board.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void initialize_board(char board[][8])
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

static void initialize_color(Parsing* turn, char* type_turn, int* turn_figure)
{
    if (turn->round % 2 == 1) {
        *type_turn = turn->type_turn_white;
        for (int i = 0; i < 4; i++) {
            turn_figure[i] = turn->white_turn[i];
        }
    } else {
        *type_turn = turn->type_turn_black;
        for (int i = 0; i < 4; i++) {
            turn_figure[i] = turn->black_turn[i];
        }
    }
}

static void parse_white_turn(Parsing* turn, int* start, int len)
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

static void parse_black_turn(Parsing* turn, int* start, int len)
{
    int count = 0;
    if (turn->data[*start] - 'a' >= 0) {
        turn->black_figure = 'p';
        turn->black_turn[0] = turn->data[*start] - 'a';
        count++;
    } else {
        turn->black_figure = tolower(turn->data[*start]);
    }

    for (int i = *start + 1; i < len; i++) {
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

static void swap(char* a, char* b)
{
    char tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

static void cut(char* a, char* b)
{
    *b = *a;
    *a = ' ';
}

int turn_validation(Parsing* turn, char board[][8])
{
    int check_turn[4];
    char figure;
    char type_turn;
    if (turn->round % 2 == 1) {
        figure = turn->white_figure;
        type_turn = turn->type_turn_white;
        for (int i = 0; i < 4; i++) {
            check_turn[i] = turn->white_turn[i];
        }
    } else {
        figure = turn->black_figure;
        type_turn = turn->type_turn_black;
        for (int i = 0; i < 4; i++) {
            check_turn[i] = turn->black_turn[i];
        }
    }
    for (int i = 0; i < 4; i++) {
        if (check_turn[i] > 8) {
            printf("Invalid data\n");
            return -1;
        }
    }
    if (figure != board[check_turn[1]][check_turn[0]]) {
        printf("Invalid figure(%c) %c\n",
               figure,
               board[check_turn[1]][check_turn[0]]);
        return -1;
    }
    if (type_turn == 'x') {
        if (turn->round % 2 == 1) {
            if (board[check_turn[3]][check_turn[2]] == ' '
                || isupper(board[check_turn[3]][check_turn[2]])) {
                printf("Invalid target\n");
                return -1;
            }
        } else {
            if (board[check_turn[3]][check_turn[2]] == ' '
                || islower(board[check_turn[3]][check_turn[2]])) {
                printf("Invalid target\n");
                return -1;
            }
        }
    }
    if (type_turn == '-') {
        if (board[check_turn[3]][check_turn[2]] != ' ') {
            printf("Invalid target\n");
            return -1;
        }
    }
    return 0;
}

int pawn_move(Parsing* turn, char board[][8])
{
    int max_turn = 1;
    int k;
    int pawn_turn[4];
    if (turn->round % 2 == 1) {
        k = 1;
        for (int i = 0; i < 4; i++) {
            pawn_turn[i] = turn->white_turn[i];
        }
        if (pawn_turn[1] == 1) {
            max_turn++;
        }
    } else {
        k = -1;
        for (int i = 0; i < 4; i++) {
            pawn_turn[i] = turn->black_turn[i];
        }
        if (pawn_turn[1] == 6) {
            max_turn++;
        }
    }
    if (pawn_turn[0] != pawn_turn[2]) {
        return -1;
    }
    if ((pawn_turn[3] - pawn_turn[1]) * k > max_turn
        || (pawn_turn[3] - pawn_turn[1]) * k <= 0) {
        return -1;
    }
    if (turn->round % 2 == 1) {
        for (int i = pawn_turn[1] + 1; i <= pawn_turn[3]; i++) {
            if (board[i][pawn_turn[2]] != ' ') {
                return -1;
            }
        }
    } else {
        for (int i = pawn_turn[1] - 1; i >= pawn_turn[3]; i--) {
            if (board[i][pawn_turn[2]] != ' ') {
                return -1;
            }
        }
    }
    swap(&board[pawn_turn[1]][pawn_turn[0]],
         &board[pawn_turn[3]][pawn_turn[2]]);
    return 0;
}

int pawn_cut(Parsing* turn, char board[][8])
{
    int k;
    int pawn_turn[4];
    if (turn->round % 2 == 1) {
        k = 1;
        for (int i = 0; i < 4; i++) {
            pawn_turn[i] = turn->white_turn[i];
        }
    } else {
        k = -1;
        for (int i = 0; i < 4; i++) {
            pawn_turn[i] = turn->black_turn[i];
        }
    }
    if (pawn_turn[0] == pawn_turn[2]) {
        return -1;
    }
    if (pawn_turn[2 + k] - pawn_turn[2 - k] > 1
        || pawn_turn[2 + k] - pawn_turn[2 - k] <= 0) {
        return -1;
    }
    if (abs(pawn_turn[1 + k] - pawn_turn[1 - k]) > 1) {
        return -1;
    }
    cut(&board[pawn_turn[1]][pawn_turn[0]], &board[pawn_turn[3]][pawn_turn[2]]);
    return 0;
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
    parse_white_turn(turn, &count, len);
    count++;
    parse_black_turn(turn, &count, len);
}

int knight_move(Parsing* turn, char board[][8])
{
    int knight_turn[4];
    char turn_type;
    initialize_color(turn, &turn_type, knight_turn);
    int letter = abs(knight_turn[1] - knight_turn[3]);
    int number = abs(knight_turn[0] - knight_turn[2]);
    if ((letter + number != 3) || letter == 0 || number == 0) {
        return -1;
    }
    if (turn_type == 'x') {
        cut(&board[knight_turn[1]][knight_turn[0]],
            &board[knight_turn[3]][knight_turn[2]]);
        return 0;
    }
    swap(&board[knight_turn[1]][knight_turn[0]],
         &board[knight_turn[3]][knight_turn[2]]);
    return 0;
}

int rook_move(Parsing* turn, char board[][8])
{
    int rook_turn[4];
    char type_turn;
    initialize_color(turn, &type_turn, rook_turn);
    if (rook_turn[1] != rook_turn[3] && rook_turn[2] != rook_turn[0]) {
        return -1;
    }
    int check = rook_turn[0], k;
    if (rook_turn[0] > rook_turn[2] || rook_turn[1] > rook_turn[3]) {
        k = -1;
    } else {
        k = 1;
    }
    while (check != rook_turn[2]) {
        check += k;
        if (check == rook_turn[2]) {
            break;
        }
        if (board[rook_turn[1]][check] != ' ') {
            return -1;
        }
    }
    check = rook_turn[1];
    while (check != rook_turn[3]) {
        check += k;
        if (check == rook_turn[3]) {
            break;
        }
        if (board[check][rook_turn[0]] != ' ') {
            return -1;
        }
    }
    if (type_turn == 'x') {
        cut(&board[rook_turn[1]][rook_turn[0]],
            &board[rook_turn[3]][rook_turn[2]]);
    } else {
        swap(&board[rook_turn[1]][rook_turn[0]],
             &board[rook_turn[3]][rook_turn[2]]);
    }
    return 0;
}

int bishop_move(Parsing* turn, char board[][8])
{
    int bishop_turn[4];
    char turn_type;
    initialize_color(turn, &turn_type, bishop_turn);
    if (bishop_turn[1] == bishop_turn[3] || bishop_turn[0] == bishop_turn[2]) {
        return -1;
    }
    if (abs(bishop_turn[1] - bishop_turn[3])
        != abs(bishop_turn[0] - bishop_turn[2])) {
        return -1;
    }
    int horizontal, vertical;
    if (bishop_turn[0] > bishop_turn[2]) {
        vertical = -1;
    } else {
        vertical = 1;
    }
    if (bishop_turn[1] > bishop_turn[3]) {
        horizontal = -1;
    } else {
        horizontal = 1;
    }
    for (int i = bishop_turn[0] + vertical, j = bishop_turn[1] + horizontal;
         i != bishop_turn[2];
         i += vertical, j += horizontal) {
        printf("%d %d %c\n", i, j, board[j][i]);
        if (board[j][i] != ' ') {
            return -1;
        }
    }
    if (turn_type == '-') {
        swap(&board[bishop_turn[1]][bishop_turn[0]],
             &board[bishop_turn[3]][bishop_turn[2]]);
        return 0;
    }
    cut(&board[bishop_turn[1]][bishop_turn[0]],
        &board[bishop_turn[3]][bishop_turn[2]]);
    return 0;
}

int queen_move(Parsing* turn, char board[][8])
{
    if (turn->round % 2 == 1) {
        if (turn->white_turn[0] == turn->white_turn[2]
            || turn->white_turn[1] == turn->white_turn[3]) {
            return rook_move(turn, board);
        } else {
            return bishop_move(turn, board);
        }
    } else {
        if (turn->black_turn[0] == turn->black_turn[2]
            || turn->black_turn[1] == turn->black_turn[3]) {
            return rook_move(turn, board);
        } else {
            return bishop_move(turn, board);
        }
    }
}