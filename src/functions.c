#include <stdlib.h>
#include <stdio.h>
#include "functions.h"

//Funções auxiliares.

/*
    Função preenche 'parsed_board' conforme o tabuleiro 'read_board' recebido como parametro,
    substituindo os pontos '.' por zero.
*/
void parse_board(char *read_board, int *parsed_board)
{
    int i;
    for (i = 0; i < 81; i++)
    {
        int value = 0;
        if (read_board[i] != '.')
        {
            value = (int)(read_board[i]) - '0';
        }
        parsed_board[i] = value;
    }
}

/*
    Imprime de forma legível uma instância de sudoku recebida como parâmetro
*/
void print_pretty_Game(int *board)
{
    int i, j;
    int c;
    for (i = 0; i < 9; i++)
    {
        if (i == 3 || i == 2 * 3)
            printf("---------+---------+---------\n");
        for (j = 0; j < 9; j++)
        {
            if (j == 3 || j == 2 * 3)
                printf("|");
            c = '.';
            if (board[i * 9 + j] != 0)
                c = (int)('0' + board[i * 9 + j]);
            printf(" %c ", c);
        }
        printf("\n");
    }
    printf("\n");
}

/*
    Imprime em uma linha uma instância de sudoku recebida como parâmetro
*/
void print_game_oneline(int *board)
{
    int i;
    int c;
    for (i = 0; i < 81; i++)
    {
        c = board[i] + '0';
        if (c == '0')
        {
            c = '.';
        }
        printf("%c", c);
    }
    printf("\n");
}

/*
    Função verifica se um valor 'value' pode ser inserido na posição 'index' de
    uma instância de sudoku 'board', de acordo com as regras do sudoku.
    Retorna 1 caso seja válido, ou 0 caso contrário.
*/
int is_valid(int value, int *board, int index, int table[81][20] )
{
    for (int i = 0; i < 20; i++) // verifica cada uma das 20 posições conflitantes à posição 'index'
    {
        if (board[table[index][i]] == value)
        {
            return 0;
        }
    }
    return 1;
}

/*
    Função verifica se uma instância de sudoku é uma solução válida.
    Retorna 1 caso positivo, ou 0 caso negativo.
*/
int is_goal(int *board, int table[81][20])
{
    for (int i = 0; i < 81; i++)
    {
        if (board[i] == 0 && is_valid(board[i], board, i, table) == 0)
            return 0;
    }
    return 1;
}

/*
    Função encontra o primeiro indíce vazio do tabuleiro passado como parametro,
    pesquisando a partir da posição 'lastEmpty'.
    Retorna o  primeiro índice vazio, ou -1 caso o tabuleiro esteja completo.
*/
int next_empty(int *board)
{
    for (int i = 0; i < 81; i++)
    {
        if (board[i] == 0)
            return i;
    }
    return -1;
}

/*
    Função move todos os valores de um tabuleiro para outro.
*/
void move_board(int *board_from, int *board_to)
{
    for (int i = 0; i < 81; i++)
        board_to[i] = board_from[i];
}

/*
    Função retorna uma cópia alocada de um tabuleiro recebido como parametro.
*/
int *deep_board_copy(int *board)
{
    int *copy = (int *)malloc(81 * sizeof(int));
    move_board(board, copy);
    return copy;
}

/*
    Função retorna 1 se 'value' está presente em 'arr', ou 0 caso contrário.
*/
int contains(int *arr, int size, int value)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == value)
            return 1;

    return 0;
}

/*
    Função transforma todos os caracteres alfabéticos de uma string em maiusculo
*/
void to_upper(char *string)
{
    const char OFFSET = 'a' - 'A';
    while (*string)
    {
        if (*string >= 'a' && *string <= 'z')
            *string -= OFFSET;
        string++;
    }
}