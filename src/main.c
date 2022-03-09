#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "functions.h"
#include "neighb-table.h"
#include "bfs.h"
#include "dfs.h"
#include "astar.h"
#include "ac3.h"
#include "backtracking.h"
#include "backtracking-ac3.h"
// #include <time.h>

/*
    Função retorna processa a entrada do usuário para escolher um algorimo,
    retornando um inteiro conforme segue:

    0: BFS
    1: DFS
    2: A*
    3: AC3
    4: Backtracking
   -1: inválido
*/
int get_algorithm(char *alg)
{
    to_upper(alg);
    if (strcmp(alg, "BFS") == 0)
        return 0;

    if (strcmp(alg, "DFS") == 0)
        return 1;

    if (strcmp(alg, "ASTAR") == 0 || strcmp(alg, "A-STAR") == 0 || strcmp(alg, "AS") == 0)
        return 2;

    if (strcmp(alg, "BACKTRACKING") == 0 || strcmp(alg, "BT") == 0)
        return 3;

    if (strcmp(alg, "BACKTRACKING-AC3") == 0 || strcmp(alg, "BACKTRACKINGAC3") == 0 || strcmp(alg, "BTAC3") == 0 || strcmp(alg, "BT-AC3") == 0)
        return 4;

    return -1;
}

int main(int argc, char const *argv[])
{
    // clock_t start = clock();
    NeighbTable nTable = get_NeghbTable(); // preenche a dep-table que será utilizada em todas as entradas

    int algorithm = get_algorithm((char *)argv[1]);
    if (algorithm == -1)
    {
        printf("Algoritmo não identificado\n");
        printf("Certifique-se de que a entrada foi do tipo ");
        printf("\"make run algoritmo entrada.txt\"\n");
        return 1;
    }

    FILE *file;
    file = fopen(argv[2], "r");
    if (file == NULL)
    {
        printf("Nao foi possivel abrir o arquivo.\n");
        printf("Certifique-se de que a entrada foi do tipo ");
        printf("\"./sudoku algoritmo entrada.txt\"\n");
        return 2;
    }

    char board_string[81 + 2];
    int board_arr[81];
    int *result = NULL;


    while (fgets(board_string, 81 + 2, file) != NULL && strlen(board_string) >= 81)
    {
        parse_board(board_string, board_arr);

        switch (algorithm)
        {
        case 0:
            result = solve_BFS(board_arr, nTable);
            break;
        case 1:
            result = solve_DFS(board_arr, nTable);
            break;
        case 2:
            result = solve_Astar(board_arr, nTable);
            break;
        case 3:
            result = solve_backtracking(board_arr, nTable);
            break;
        case 4:
            result = solve_backtrackingAC3(board_arr, nTable);
            break;
        default:
            break;
        }

        if (result)
        {
            print_game_oneline(result);
            FREE(result);
        }
        else
        {
            printf("Sem solução\n");
        }
    }


    fclose(file);
    FREE(nTable);

    // printf("Time: %.4f sec.\n", (float)(clock() - start) / CLOCKS_PER_SEC);
    return 0;
}