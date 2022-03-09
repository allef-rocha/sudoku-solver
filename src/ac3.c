#include <stdlib.h>
#include <stdio.h>
#include "neighb-table.h"
#include "functions.h"
#include "ac3.h"

/*
    Estrutura que representa um nó da fila de arcos
*/
typedef struct node_ArcQueue *NodeArcQueue;
struct node_ArcQueue
{
    int node[2];
    NodeArcQueue next, prev;
};

/*
    Função cria nó da fila de arcos
*/
NodeArcQueue create_nodeArcQueue(int indexA, int indexB)
{
    NodeArcQueue n = (NodeArcQueue)malloc(sizeof(struct node_ArcQueue));
    n->node[0] = indexA;
    n->node[1] = indexB;
    n->next = NULL;
    n->prev = NULL;
    return n;
}

/*
    Fila que armazena os arcos.
*/
struct arc_queue
{
    NodeArcQueue head, tail;
};
typedef struct arc_queue *ArcQueue;


/*
    Função cria fila de arcos
*/
ArcQueue create_ArcQueue()
{
    ArcQueue al = (ArcQueue)malloc(sizeof(struct arc_queue));
    al->head = NULL;
    al->tail = NULL;
    return al;
}

/*
    Desaloca a fila, bem como todos seus nós.
*/
void destroy_ArcQueue(ArcQueue queue)
{
    if (queue == NULL)
        return;
    if (queue->head == NULL)
    {
        FREE(queue);
        return;
    }
    NodeArcQueue curr = queue->head;
    while (curr != NULL)
    {
        NodeArcQueue tmp = curr;
        curr = curr->next;
        FREE(tmp);
    }
    FREE(queue);
}

/*
    Função enfilera
*/
void enqueue(ArcQueue queue, int A, int B)
{
    if (queue == NULL)
        queue = create_ArcQueue();

    NodeArcQueue new_node = create_nodeArcQueue(A, B);

    NodeArcQueue prev_tail = queue->tail;

    if (prev_tail == NULL)
    {
        queue->tail = new_node;
        queue->head = new_node;
        return;
    }
    prev_tail->next = new_node;
    new_node->prev = prev_tail;
    queue->tail = new_node;
    return;
}

/*
    Função remove primeiro da fila
*/
void pop(ArcQueue queue, int taken[2])
{
    NodeArcQueue tmp = queue->head;

    if (tmp == NULL)
        return;

    taken[0] = tmp->node[0];
    taken[1] = tmp->node[1];

    queue->head = tmp->next;

    if (queue->head == NULL)
        queue->tail = NULL;
    else
        queue->head->prev = NULL;

    FREE(tmp);
}

/*
    Função informa se a fila está vazia.
    Retorna 1 caso positivo, e 0 caso contrário.
*/
int is_empty_queue(ArcQueue queue)
{
    return queue == NULL || queue->head == NULL;
}

/*
    Função conta o número de possibilidades para um dado índice,
    considerando o domínio passado como parâmetro.
    Retorna o número de possibilidades para o índice.
*/
int domain_size(int index, int domain[81][9])
{
    int possib = 0;
    for (int i = 1; i <= 9; i++)
        possib += domain[index][i - 1];
    return possib;
}

/*
    Função inicializa o domínio levando em consideração as restrições
    aplicáveis à instância de sudoku recebida como parâmetro
*/
void init_domain(int domain[81][9], int *board, NeighbTable nTable)
{
    for (int i = 0; i < 81; i++)
    {
        if (board[i] != 0)
        {
            domain[i][board[i] - 1] = 1;
            continue;
        }
        for (int v = 1; v <= 9; v++)
        {
            if (is_valid(v, board, i, nTable->table))
            {
                domain[i][v - 1] = 1;
            }
        }
    }
}


/*
    Função revisa o dominio de 'a'.
    Retorna 1 caso tenha feito alguma revisão, e 0 caso contrário.
*/
int revise(int domain[81][9], int a, int b)
{
    int revised = 0;
    for (int i = 0; i < 9; i++)
    {
        if (domain[a][i] == 0)
        {
            continue;
        }
        int empty_domain = 1;
        for (int j = 0; j < 9; j++)
        {
            if (i != j && domain[b][j] == 1)
            {
                empty_domain = 0;
                break;
            }
        }
        if (empty_domain)
        {
            domain[a][i] = 0;
            revised = 1;
        }
    }
    return revised;
}

/*
    Função aplica o algorítimo AC3 para um domínio recebido como parâmetro
*/
int AC3(int domain[81][9], NeighbTable nTable)
{
    ArcQueue queue = create_ArcQueue();
    for (int i = 0; i < 81; i++)
    {
        for (int j = 0; j < 20; j++)
            enqueue(queue, i, nTable->table[i][j]);
    }

    while (!is_empty_queue(queue))
    {
        int arc[2];     // arc[0] = x, arc[1] = y
        pop(queue, arc);

        if (revise(domain, arc[0], arc[1])) 
        {
            if (domain_size(arc[0], domain) == 0)  // se o domínio de foi destruído, retorna 0
            {
                destroy_ArcQueue(queue);
                return 0;
            }
            for (int i = 0; i < 20; i++)    // todo vizinho de z de x, t.q. z != y
            {
                int neighb = nTable->table[arc[0]][i];
                if (neighb == arc[1])
                    continue;
                enqueue(queue, neighb, arc[0]);
            }
        }
    }
    destroy_ArcQueue(queue);
    return 1;
}