#ifndef BOARD_H
#define BOARD_H

typedef struct {
    char data[30]; //необработанные входные данные
    int white_turn[4];
    int black_turn[4];
    char white_figure;
    char black_figure;
    char type_turn_white;
    char type_turn_black;
    int round;
} Parsing;

int knight_move(Parsing* turn, char board[][8]);

void initialize_board(char board[][8]);

int turn_validation(Parsing* turn, char board[][8]);

int rook_move(Parsing* turn, char board[][8]);

void input_data(Parsing* turn);

int pawn_move(Parsing* turn, char board[][8]);

int pawn_cut(Parsing* turn, char board[][8]);

int bishop_move(Parsing* turn, char board[][8]);

int queen_move(Parsing* turn, char board[][8]);

int king_move(Parsing* turn, char board[][8]);
#endif
