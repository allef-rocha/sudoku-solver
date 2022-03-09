#ifndef LIST_H
#define LIST_H

struct node_l
{
    int board[81];
    struct node_l *next, *prev;
    int f, g;
};
typedef struct node_l *NodeList;

struct list
{
    struct node_l *head, *tail;
};
typedef struct list *List;

List create_list();
NodeList create_node_l(int board[]);
NodeList create_Astar_node(int board[], int g, int h);
void append(List list, int board[]);
void prepend(List list, int board[]);
void insert_sorted_by_f(List list, int *board, int g, int h);
int *take_first(List list);
int *take_last(List list);
int is_empty(List list);
void destroy_list(List list);

#endif // !LIST_H