#include <stdlib.h>
#include "list.h"
#include "functions.h"
#include "neighb-table.h"
#include "astar.h"

// Função heurística que retorna o número de espaços vazios no tabuleiro recebido como parâmetro
int heuristic(int *board)
{
    int count = 0;
    for (int i = 0; i < 81; i++)
    {
        if (board[i] == 0)
        {
            count++;
        }
    }
    return count;
}
/*
    Função que resolve uma instância de sudoku utilizando o algoritmo A*.
    Retorna uma cópia cópia do tabuleiro com todos espaços preenchidos, ou
    NULL caso não consiga resolver.
*/
int *solve_Astar(int *board, NeighbTable nTable)
{
    int index, g;
    List list = create_list();
    int *parentBoard, v;

    append(list, board);
    while (!is_empty(list))
    {
        g = list->head->g;
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
                // no caso positivo, ele é inserido, e um node é gerado e inserido de forma ordenada (em função de node->f) na lista
                parentBoard[index] = v;
                insert_sorted_by_f(list, parentBoard, g + 1, heuristic(parentBoard));
            }
        }
        FREE(parentBoard);
    }
    if (list)
        destroy_list(list);
    return NULL;
}