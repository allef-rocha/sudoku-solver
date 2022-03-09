#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#define FREE(ptr)     \
    do                \
    {                 \
        free((ptr));  \
        (ptr) = NULL; \
    } while (0)

void parse_board(char *read_board, int *parsed_board);
void print_pretty_Game(int *board);
void print_game_oneline(int *board);
int is_valid(int value, int *board, int index, int nTable[81][20]);
int is_goal(int *board, int nTable[81][20]);
int next_empty(int *board);
void move_board(int *board_from, int *board_to);
int *deep_board_copy(int *board);
int contains(int *arr, int size, int value);
void to_upper(char *str);

#endif // !AUX_FUNCTIONS_H