#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "functions.h"

/*
    Aloca e retorna uma lista vazia,
*/
List create_list()
{
    List q = (List)malloc(sizeof(struct list));
    if (!q)
    {
        printf("Failed to allocate memory");
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;

    return q;
}

/*
    Aloca e retorna uma nó vazio e zerado.
*/
NodeList create_node_l(int board[])
{
    NodeList n = (NodeList)malloc(sizeof(struct node_l));
    if (!n)
    {
        printf("Failed to allocate memory");
        return NULL;
    }

    for (int i = 0; i < 81; i++)
    {
        n->board[i] = board[i];
    }
    n->next = NULL;
    n->prev = NULL;
    n->f = 0;
    n->g = 0;
    return n;
}

/*
    Aloca e retorna uma nó com valores de g e h (refetentes ao A*) preenchidos.
*/
NodeList create_Astar_node(int board[], int g, int h)
{
    NodeList no = create_node_l(board);
    no->g = g;
    no->f = g + h;
    return no;
}
/*
    Insere um nó no fim da lista.
*/
void append(List list, int board[])
{
    if (list == NULL)
    {
        list = create_list();
    }

    NodeList new_node = create_node_l(board);

    NodeList prev_tail = list->tail;

    if (prev_tail == NULL)
    {
        list->tail = new_node;
        list->head = new_node;
        return;
    }
    prev_tail->next = new_node;
    new_node->prev = prev_tail;
    list->tail = new_node;
    return;
}

/*
    Insere um nó no começo da lista.
*/
void prepend(List list, int board[])
{
    if (list == NULL)
    {
        list = create_list();
    }

    NodeList new_node = create_node_l(board);

    NodeList prev_head = list->head;

    if (prev_head == NULL)
    {
        list->tail = new_node;
        list->head = new_node;
        return;
    }
    new_node->next = prev_head;
    prev_head->prev = new_node;
    list->head = new_node;
    return;
}

/*
    Cria um nó e o insere na lista de forma ordenada de acordo com o valor 
    de f (node->f). Em caso de empate, o nó é adcionado após os demais nós
    com mesmo valor.
*/
void insert_sorted_by_f(List list, int *board, int g, int h)
{
    NodeList no = create_Astar_node(board, g, h);
    if (list->tail == NULL)
    {
        list->head = no;
        list->tail = no;
        return;
    }
    if (no->f >= list->tail->f)
    {
        list->tail->next = no;
        no->prev = list->tail;
        list->tail = no;
        return;
    }

    NodeList curr = list->tail;
    while (curr->prev != NULL && curr->prev->f > no->f)
    {
        curr = curr->prev;
    }
    if (curr == list->head)
    {
        no->next = curr;
        curr->prev = no;
        list->head = no;
        return;
    }
    NodeList tmp = curr->prev;
    curr->prev = no;
    no->next = curr;
    no->prev = tmp;
    tmp->next = no;
}

/*
    Retorna o primeiro nó da lista.
*/
int *take_first(List list)
{
    NodeList tmp = list->head;

    if (tmp == NULL)
        return NULL;

    int *retval = deep_board_copy(tmp->board);

    list->head = tmp->next;

    if (list->head == NULL)
    {
        list->tail = NULL;
    }
    else
    {
        list->head->prev = NULL;
    }
    FREE(tmp);

    return retval;
}

/*
    Retorna o último nó da lista.
*/
int *take_last(List list)
{
    NodeList tmp = list->tail;

    if (tmp == NULL)
        return NULL;

    int *retval = deep_board_copy(tmp->board);

    list->tail = tmp->prev;

    if (list->tail == NULL)
    {
        list->head = NULL;
    }
    else
    {
        list->tail->next = NULL;
    }
    FREE(tmp);

    return retval;
}

/*
    Retorna 1 caso a lista esteja vazia, ou 0 caso contrário.
*/
int is_empty(List list)
{
    return list == NULL || list->head == NULL;
}

/*
    Desaloca a lista, bem como todos seus nós.
*/
void destroy_list(List list)
{
    if (list == NULL)
    {
        return;
    }
    if (list->head == NULL)
    {
        FREE(list);
        return;
    }
    NodeList curr = list->head;
    while (curr != NULL)
    {
        NodeList tmp = curr;
        curr = curr->next;
        FREE(tmp);
    }
    FREE(list);
}