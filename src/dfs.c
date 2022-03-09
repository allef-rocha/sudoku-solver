#include <stdlib.h>
#include "neighb-table.h"
#include "functions.h"
#include "dfs.h"

/*
    Função resolve recursivamente uma instância de um sudoku utilizano o algoritimo
    de Busca em Largura. Retorna 1 caso consiga resolver, ou 0 caso contrário. 
*/
int solve_DFS_rec(int *board, NeighbTable nTable)
{
    int index = next_empty(board);
    if (index == -1)
    {
        // Ao atingir o objetivo, retorna 1, informando que a cadeia recursiva até aqui
        // gerou uma solução válidas.
        return is_goal(board, nTable->table);
    }
    for (int v = 1; v <= 9; v++) // é verificado para cada valor 'v' se ele é válido na posição 'index'
    {
        if (is_valid(v, board, index, nTable->table)) // caso positivo, ele é inserido, e a função é chamada recursivamente
        {
            board[index] = v;
            if (solve_DFS_rec(board, nTable))
            // caso essa solução parcial componha uma solução, a cadeia recursiva é desfeita retornando 1 sucessivamente
            {
                return 1;
            }
        }
        // caso essa solução parcial não componha uma solução, a posição 'index' volta a ficar vazia
        board[index] = 0;
    }
    return 0;
}

/*
    Função chama função 'solve_DFS_rec()' que resolve a instância do sudoku recursivamente.
    Caso a instância seja resolvida, é retornado uma cópia alocada do tabuleiro com todos
    os espaços preenchidos. Caso contrário, é retornado NULL.
*/
int *solve_DFS(int *board, NeighbTable nTable)
{
    if (solve_DFS_rec(board, nTable))
        return deep_board_copy(board);

    return NULL;
}