#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "neighb-table.h"
#include "functions.h"
#include "ac3.h"
#include "backtracking-ac3.h"


/*
    Função verifica se todos os valores tem domínio unitário
    Retorna
         1 - caso positivo
         0 - caso negativo
        -1 - caso algum domínio seja vazio
*/
int all_singleton(int domain[81][9])
{
    int singleton = 1;
    for (int i = 0; i < 81; i++)
    {
        int count = 0;
        for (int j = 0; j < 9 && count < 2; j++)
            count += domain[i][j];
        
        if (count == 0)
            return -1;
        
        if (count > 1)
            singleton = 0;
    }
    return singleton;
}

/*
    Função preenche o tabuleiro com o valor válido do domínio.
    Só deve ser utilizada após verificar se os dominíos são todos singleton
*/
void fill_board(int *board, int domain[81][9])
{
    for (int i = 0; i < 81; i++)
    {
        if (board[i] != 0)
            continue;
        int v;
        for (v = 1; v < 9 && domain[i][v - 1] == 0; v++)
            continue;
        board[i] = v;
    }
}

/*
    Função seleciona o índice com o menor número de valores no domínio.
*/
int selec_index(int *board, int domain[81][9])
{
    int min = 9;
    int min_index = 0;
    for (int i = 0; i < 81; i++)
    {
        if (board[i] != 0)
            continue;
        int count = 0;
        for (int j = 0; j < 9 && count < min; j++)
        {
            count += domain[i][j];
        }
        if (count == 1)
        {
            return i;
        }
        if (count < min)
        {
            min = count;
            min_index = i;
        }
    }
    return min_index;
}

/*
    Função assign utilizada no algorítmo de backtracking
*/
int assign(int index, int value,  int *board, int domain[81][9], NeighbTable nTable)
{
    board[index] = value;
    for (int k = 0; k < 9; k++)
    {
        domain[index][k] = 0;
    }
    domain[index][value - 1] = 1;
    return AC3(domain, nTable);
}

/*
    Função recursiva utilizada para encontrar a solução de uma instância de sudoku.
    Retorna 1 caso uma solução tenha sido encontrada, e 0 caso o caminho recursivo tenha levado a uma
    situação infactível.
*/
int solve_backtrackingAC3_rec(int *board, int domain[81][9], NeighbTable nTable)
{
    int verify = all_singleton(domain);
    if (verify == -1) // Um dos domínios é vazio
        return 0;

    if (verify == 1) // Todos os domínios são singleton
    {
        fill_board(board, domain);
        return 1;
    }

    int index = selec_index(board, domain);
    int domain_copy[81][9];
    memcpy(domain_copy, domain, 81 * 9 * sizeof(int));
    for (int v = 1; v <= 9; v++)
    {
        if (domain[index][v - 1] == 0)
            continue;
        int assignment = assign(index, v, board, domain_copy, nTable);
        if (assignment)
        {
            if (solve_backtrackingAC3_rec(board, domain_copy, nTable))
                return 1;
        }
        board[index] = 0;
        memcpy(domain_copy, domain, 81 * 9 * sizeof(int));
    }
    return 0;
}

/*
    Função chama a função solve_backtrackingAC3_rec, que resolve recursivamente a instância do sudoku.
    Retorna uma cópia do tabuleiro preenchido, caso tenha encontrado uma solução.
    Retorna NULL caso contrário.
*/
int *solve_backtrackingAC3(int *board, NeighbTable nTable)
{
    int domain[81][9] = {0};
    init_domain(domain, board, nTable);
    if (!AC3(domain, nTable))
    {
        return NULL;
    }
    if (solve_backtrackingAC3_rec(board, domain, nTable))
    {
        return deep_board_copy(board);
    }
    return NULL;
}