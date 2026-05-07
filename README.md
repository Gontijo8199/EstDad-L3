# Trabalho 3: Sistema de Matchmaking para Jogos Online

**Alunos:**
- Rafael Gontijo Ferreira
- Rudá Dantas Ruoso Brandão

---

## Descrição

Este projeto consiste na realização da terceira atividade da disciplina de Estrutura de Dados, implementando um sistema de **matchmaking** para jogadores em busca de partidas online.

O sistema é responsável por:

- armazenar jogadores em uma fila de espera;
- ordenar os jogadores por score utilizando dois algoritmos distintos;
- formar grupos de jogadores com níveis de habilidade semelhantes.

Cada jogador possui:

- um identificador único (`id`);
- um nome (`name`);
- um score, representando seu nível de habilidade (`score`);
- um timestamp, representando sua ordem de chegada na fila (`timestamp`).

A ideia central é explorar a **ordenação** dos jogadores para facilitar a busca por grupos válidos: ao ordenar por score, basta verificar janelas consecutivas de tamanho `groupSize` para checar se a diferença entre o maior e o menor score é menor ou igual ao `delta` permitido.

Instrução de compilação:

```bash
g++ main.cpp Matchmaking.cpp Player.cpp -o matchmaking
```

Instrução de execução:

```bash
./matchmaking
```

---

## Organização do Projeto

O sistema está dividido nos seguintes arquivos:

- `main.cpp` — função principal com os casos de teste do sistema;
- `Player.hpp` — declaração da classe `Player`;
- `Player.cpp` — implementação da classe `Player`;
- `Matchmaking.hpp` — declaração da classe `Matchmaking`;
- `Matchmaking.cpp` — implementação da classe `Matchmaking` com os algoritmos de ordenação, formação de grupos e demais operações.

---

## Estrutura de Dados

A classe `Matchmaking` armazena os jogadores em um **array estático** de tamanho `MAX_PLAYERS = 100000`, acompanhado de um inteiro `size` que rastreia a quantidade atual de jogadores na fila.

```cpp
Player players[MAX_PLAYERS];
int size;
```

Essa abordagem garante acesso em tempo constante por índice e evita o uso de estruturas da STL, conforme exigido pelo enunciado.

---

## Algoritmos de Ordenação

### Insertion Sort — `sortByScoreInsertion()`

O insertion sort percorre o array da esquerda para a direita. Para cada novo elemento na posição `i`, ele é deslocado para a esquerda até encontrar sua posição correta dentre os elementos já ordenados. A comparação segue dois critérios:

1. score em ordem crescente;
2. em caso de empate, timestamp em ordem crescente.

**Complexidade:** O(n²) no pior caso, O(n) para entradas quase ordenadas.

### Merge Sort — `sortByScoreMerge()`

O merge sort utiliza a estratégia de **divisão e conquista** com recursão. A cada chamada, o segmento atual é dividido ao meio, cada metade é ordenada recursivamente e então as duas metades são intercaladas em um array auxiliar alocado dinamicamente, que depois é copiado de volta para o array original.

O critério de comparação é o mesmo do insertion sort: score crescente, com desempate por timestamp crescente.

**Complexidade:** O(n log n) no pior caso.

---

## Formação de Grupos — `formGroup()`

O método `formGroup(groupSize, delta, &n)` assume que os jogadores já estão ordenados por score e varre o array com uma **janela deslizante** de tamanho `groupSize`. Para cada posição `i`, verifica se:

```
players[i + groupSize - 1].score - players[i].score <= delta
```

Caso a condição seja satisfeita, o primeiro grupo válido encontrado é copiado para um novo array alocado dinamicamente, os jogadores são removidos da fila, `*n` recebe `groupSize` e o grupo é retornado.

Caso nenhum grupo válido seja encontrado, o método retorna `nullptr` e define `*n = 0`, sem alterar a fila.

A memória alocada para o array retornado deve ser liberada pelo chamador com `delete[]`.

---

## Casos de Teste (`main.cpp`)

O `main.cpp` cobre os seguintes cenários:

| Teste | Descrição |
|-------|-----------|
| `teste_1_1` | Inserção de jogadores já ordenados por score |
| `teste_1_2` | Inserção de jogadores fora de ordem |
| `teste_2_1` | Ordenação via insertion sort sem empate |
| `teste_2_2` | Ordenação via insertion sort com empate de score |
| `teste_3_1` | Ordenação via merge sort sem empate |
| `teste_3_2` | Ordenação via merge sort com empate de score |
| `teste_4_1` | Formação de grupo bem-sucedida (delta permissivo) |
| `teste_4_2` | Tentativa de formação de grupo sem sucesso (delta restritivo) |

Para executar todos os testes, basta compilar e executar o programa conforme as instruções acima.

---

## Observações

- Nenhuma estrutura da STL (`vector`, `list`, `map`, `queue`, `stack`, etc.) foi utilizada na implementação.
- Nenhuma função pronta de ordenação (`std::sort` ou similar) foi utilizada.
- O gerenciamento de memória dos arrays retornados por `formGroup` e `getWaitingPlayers` é responsabilidade do chamador.