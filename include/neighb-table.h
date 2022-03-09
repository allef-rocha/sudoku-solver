#ifndef DEP_TABLE_H
#define DEP_TABLE_H

struct neighbTable{
    int table[81][20];
};

typedef struct neighbTable* NeighbTable;

int write_table(NeighbTable nTable);
int read_table(NeighbTable nTable);
NeighbTable get_NeghbTable();

#endif // !DEP_TABLE_H