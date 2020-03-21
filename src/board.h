#ifndef BOARD_H 
#define BOARD_H  

typedef struct{
    char data[30];//необработанные входные данные
    int white_turn[4];
    int black_turn[4];
    char white_figure;
    char black_figure;
    char type_turn_white;
    char type_turn_black;
    int* round;
}Parsing;

void cut(char* a, char* b);

int white_knight(Parsing* turn, char board[][8]);

int black_knight(Parsing* turn, char board[][8]);

void parsing_white(Parsing* turn, int* start, int len);

void parsing_black(Parsing* turn, int* start, int len);

void initiate_board(char board[][8]);

void swap(char *a, char *b);

int check(Parsing* turn,char board[][8]);

void input_data(Parsing* turn);

int white_pawn(Parsing* turn, char board[][8]);

int black_pawn(Parsing* turn, char board[][8]);
#endif
