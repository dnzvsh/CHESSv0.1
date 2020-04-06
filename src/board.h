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

int knight_move(int* knight_turn, char turn_type, char board[][8]);

void initialize_board(char board[][8]);

int turn_validation(
        int round,
        int* check_turn,
        char figure,
        char type_turn,
        char board[][8]);

int rook_move(int* rook_turn, char type_turn, char board[][8]);

void input_data(Parsing* turn);

int pawn_move(int round, int* pawn_turn, char type_turn, char board[][8]);

int bishop_move(int* bishop_turn, char turn_type, char board[][8]);

int queen_move(int* queen_turn, char type_turn, char board[][8]);

int turn_figure(
        int* round,
        int* figure_turn,
        char figure,
        char type_turn,
        char board[][8]);

int king_move(int* king_turn, char turn_type, char board[][8]);

void parse_round(Parsing* turn, char* data);
#endif
