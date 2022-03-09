# Sudoku

Projeto desenvolvido para a disciplina de Inteligência Arificial
UFABC - 2021.Q1 - Prof. Fabrício Olivetti de França (folivetti@ufabc.edu.br)

# Descrição

Nesse projeto são utilizados diferentes algoritmos capazes de resolver uma instância do jogo Sudoku. Foram implementados os seguintes:

- Busca em largura
- Busca em profundidade
- Busca A*
- AC-3
- Backtracking


Exemplo de entrada:

```
.......2143.......6........2.15..........637...........68...4.....23........7....
.......241..8.............3...4..5..7.....1......3.......51.6....2....5..3...7...
.......24....1...........8.3.7...1..1..8..5.....2......2.4...6.5...7.3...........
.......23.1..4....5........1.....4.....2...8....8.3.......5.16..4....7....3......
.......21...5...3.4..6.........21...8.......75.....6.....4..8...1..7.....3.......
.......215.3......6...........1.4.6.7.....5.....2........48.3...1..7....2........
.......21.9.7.................514...63............2......6..93...1.4....2.....8..
.......314...2.........7......3.1.5.7..5.....2.6..........8.2...3.6...........4..
```

Exemplo de saída:

```
857349621432861597619752843271583964945126378386497215768915432194238756523674189
867351924143829765295746813318472596724695138956138247489513672672984351531267489
815369724294718653736524981387645192142897536659231478921453867568172349473986215
497185623312649857586732941138596472975214386264873519829357164641928735753461298
369784521187592436452613798746821953823965147591347682275436819914278365638159274
879543621523716489641829735385194267792638514164257893956481372418372956237965148
758439621194726358326158497879514263632897145415362789547681932981243576263975814
827456931461923587395817624984361752713592846256748319649185273532674198178239465
```

Cada linha representa um problema do Sudoku, por exemplo, a linha

```
.......2143.......6........2.15..........637...........68...4.....23........7....
```

representa a grade

```
. . . | . . . | . 2 1
4 3 . | . . . | . . .
6 . . | . . . | . . .
------+-------+------
2 . 1 | 5 . . | . . .
. . . | . . 6 | 3 7 .
. . . | . . . | . . .
------+-------+------
. 6 8 | . . . | 4 . .
. . . | 2 3 . | . . .
. . . | . 7 . | . . .
```

em que os `.` representam valores a serem preenchidos.


## Requisitos

Você vai precisar:
- gcc
- make

## Compilação

Abra um terminal no diretório onde está o Makefile e digite:

`make`


Os arquivos serão compilados, gerando um *object file* para cada código fonte, bem como o executável **sudoku** na pasta */bin*.

Para remover os arquivos *.o* gerados, digite:

`make clean`


E para remover os arquivos *.o*, bem como o executável gerado, digite:

`make remove`


## Execução

Para executar o programa, digite:

`make run algoritmo entrada.txt`

Onde **algoritmo** deve ser um dos seguintes:
- **bfs** (Busca em largura)
- **dfs** (Busca em profundidade)
- **astar** (Busca em largura)
- **backtracking** (Busca com retrocesso)
- **backtracking-ac3** (Backtracking + AC3)

E **entrada.txt** deve ser um arquivo contendo entradas válidas como as que constam na descrição.
