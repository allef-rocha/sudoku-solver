#include <stdlib.h>
#include <stdio.h>
#include "functions.h"
#include "neighb-table.h"

/*
  A tabela de vizinhança é uma tabela representada por um array bidimensional que,
  para cada um dos 81 indices de um tabuleiro, contem uma array com as 20 posições
  das quais esse índice depende. Veja o exemplo abaixo:

  . . . | c c c | . . . 
  c c c | c c X | c c c 
  . . . | c c c | . . . 
  ---------------------
  . . . | . . c | . . . 
  . . . | . . c | . . . 
  . . . | . . c | . . . 
  ---------------------
  . . . | . . c | . . . 
  . . . | . . c | . . . 
  . . . | . . c | . . . 

  Para inserir um valor na posição 'X' é necessário verificar 
  todas as 20 'c's posições.

  Essa tabela evita que uma posição seja visitada mais de uma vez, e pode
  ser utilizada para qualquer instância de sudoku.
*/

/*
  Escreve no arquivo table.data a dep-table, para evitar que sua construção
  seja refeita sempre que executar novamente o programa, já que a dep-table 
  é a mesma para qualquer sudoku 9x9.
  Retorna 1 caso a escrita tenha sido realizada, ou 0 caso contrário.
*/
int write_table(NeighbTable nTable)
{
  int written = 0;
  FILE *f = fopen("bin/table.data", "wb");
  written = fwrite(nTable->table, sizeof(int), 81 * 20, f);
  if (written == 0)
  {
    fclose(f);
    return 0;
  }
  fclose(f);
  return 1;
}

/*
  Lê o arquivo table.data refetente a dep-table, escrevendo-a
  em table[][], recebido como parâmetro.
  Retorna 1 caso a leitura tenha sido realizada, ou 0 caso contrário.
*/
int read_table(NeighbTable nTable)
{
  int read = 0;
  FILE *f = fopen("bin/table.data", "rb");
  if (f == NULL)
  {
    return 0;
  }
  read = fread(nTable->table, sizeof(int), 81 * 20, f);
  if (read == 0)
  {
    fclose(f);
    return 0;
  }
  fclose(f);
  return 1;
}

/*
  Retrona uma dep-table alocada. Caso o arquivo 'table.data' não exista,
  a tabela é montada e escrita no arquivo. Caso contrário, a tabela é
  simplesmente lida.
*/
NeighbTable get_NeghbTable()
{
  NeighbTable nTable = (NeighbTable)malloc(sizeof(struct neighbTable));
  if(nTable == NULL){
    printf("Falha ao alocar memória.\n");
    return NULL;
  }
  if (read_table(nTable))
  {
    return nTable;
  }
  for (int index = 0; index < 81; index++)
  {
    int row = index / 9;
    int col = index % 9;
    int aux_row = (row / 3) * 3;
    int aux_col = (col / 3) * 3;

    int pos = 0;
    for (int j = 0; j < 9; j++)
    {
      int keys[3] = {row * 9 + j,                                // j-ésima célula na mesma linha
                     j * 9 + col,                                // j-ésima célula na mesma coluna
                     (aux_row + j / 3) * 9 + (aux_col + j % 3)}; // j-ésima célula no mesmo quadrante

      // 'keys[key]' é um candidato a índice conflitante de 'index'.
      // Caso ele já não esteja na lista de conflitância, ou seja o próprio 'index', é adcionado, em ordem crescente
      for (int key = 0; key < 3; key++)
      {
        if (keys[key] == index)
          continue;
        if (!contains(nTable->table[index], pos, keys[key]))
        {
          int i;
          for (i = 0; i < pos; i++)
            if (nTable->table[index][i] > keys[key])
              break;

          for (int jj = pos - 1; jj >= i; jj--)
            nTable->table[index][jj + 1] = nTable->table[index][jj];

          nTable->table[index][i] = keys[key];
          pos++;
        }
      }
    }
  }
  write_table(nTable);
  return nTable;
}