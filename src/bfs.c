#include <stdlib.h>
#include "list.h"
#include "functions.h"
#include "neighb-table.h"
#include "bfs.h"

/*
    Função que resolve uma instância de sudoku utilizando o algoritmo de
    Busca em Largura*. Retorna uma cópia cópia do tabuleiro com todos 
    espaços preenchidos, ou NULL caso não consiga resolver.
*/
int *solve_BFS(int *board, NeighbTable nTable)
{
    int index;
    List list = create_list();
    int *parentBoard = NULL;
    int v;
    append(list, board);
    while (!is_empty(list))
    {
        parentBoard = take_first(list);
        index = next_empty(parentBoard);

        if (index == -1) // index = -1 significa que não há mais espaços vazios
        {
            destroy_list(list);
            return is_goal(parentBoard, nTable->table) ? parentBoard : NULL;
        }
        for (v = 1; v <= 9; v++) // é verificado para cada valor 'v' se ele é válido na posição 'index'
        {
            if (is_valid(v, parentBoard, index, nTable->table))
            {
                // caso positivo, ele é inserido, e um nó é gerado e inserido no fim da lista
                parentBoard[index] = v;
                append(list, parentBoard);
            }
        }
        FREE(parentBoard);
    }
    if (list)
        destroy_list(list);
    return NULL;
}
