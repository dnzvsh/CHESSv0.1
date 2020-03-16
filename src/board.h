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

void parsing_white(Parsing* turn, int* start, int len);

void parsing_black(Parsing* turn, int* start, int len);

void initiate_board(char board[][8]);

void swap(char *a, char *b);

void input_data(Parsing* turn);
#endif
