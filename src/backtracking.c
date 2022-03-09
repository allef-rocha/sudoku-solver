#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "neighb-table.h"
#include "functions.h"
#include "ac3.h"
#include "backtracking.h"

/*
    Função conta o número de valores possíveis no índice 'index' do tabuleiro, enquanto atualiza
    o domínio passado como parâmetro.
    Retorna o núemro de possibilidades para 'index'.
*/
int count_possib(int index, int *board, int domain[81][9], int nTable[81][20])
{
    int count = 0;
    for (int v = 1; v <= 9; v++)
    {
        int valid = is_valid(v, board, index, nTable);
        domain[index][v - 1] = valid;
        count += valid;
    }
    return count;
}

/*
    Função seleciona, entre os espaços vazios do tabuleiro, aquele que tem o menor
    número de candidatos.
    Observe que é possível que haja um espaço zero possibilidades. Nesse caso, ele
    será retornado, implicando no reconhecimento de que esse caminho recursivo não
    faz parte da solução.
    Retorna:
         0 a 80: índice que tem menos candidatos,
        -1 caso não haja espaços vazios,
        -2 caso um dos índices tenha domínio vazio


*/
int select_empty(int *board, int domain[81][9], int nTable[81][20])
{
    int minpossib = 10;
    int minindex = -1;
    for (int i = 0; i < 81; i++)
    {
        if (board[i] == 0)
        {
            int possib = count_possib(i, board, domain, nTable);

            if (possib == 0)
                return -2;

            if (possib < minpossib)
            {
                minpossib = possib;
                minindex = i;
            }
        }
        else
        {
            domain[i][board[i]-1] = 1;
        }
    }
    return minindex;
}

/*
    Função resolve recursivamente uma instância de sudoku utilizando o algoritmo
    de Backtracking.
    Retorna 1 caso o caminho recursivo seja admissível, e 0 (zero) caso contrário.
*/
int solve_backtracking_rec(int *board, NeighbTable nTable)
{
    int domain[81][9] = {0};
    int index = select_empty(board, domain, nTable->table);
    if (index == -2) // algum indice tem dominio = 0
        return 0;

    if (index == -1)
        return is_goal(board, nTable->table) ? 1 : 0;

    for (int v = 1; v <= 9; v++)
    {
        if (domain[index][v - 1])
        {
            board[index] = v;
            if (solve_backtracking_rec(board, nTable))
            {
                return 1;
            }
        }
        board[index] = 0;
    }
    return 0;
}

/*
    Função chama função 'solve_backtracking_rec()' que resolve recursivamente
    uma instância de sudoku.
    Retorna uma cópia alocada do tabuleiro resolvido, ou NULL caso não não
    consiga resolver.
*/
int *solve_backtracking(int *board, NeighbTable nTable)
{
    if (solve_backtracking_rec(board, nTable))
        return deep_board_copy(board);

    return NULL;
}
