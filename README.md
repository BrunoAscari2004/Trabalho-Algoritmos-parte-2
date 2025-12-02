# Trabalho-Algoritmos-parte-2

# Índices Hash:

Aplicamos uma indexação por hash no campo de data da tabela de pedidos. As colisões em data iguais são usadas para definir os buckets por lista encadeada, assim pode ser feito de forma muito eficiente uma consulta mostrando todos os pedido em uma data específica. Função de hash = (ano*31 + mes*31 + dia) % 96001(numero primo mais proximo do num de registros)

# Índices por arvore:

O código implementa uma Árvore B+, pois na B+ os nós internos ficam menores (sem dados), permitindo um grau maior (fan-out) e menos acessos à memória para encontrar a folha. Além disso, facilita a varredura sequencial."

Ordem/Grau da Árvore:
A ordem (M) foi calculada dinamicamente, baseada no tamanho da Página de Disco.
Foi utilizado o padrão da indústria de 4096 bytes (4KB), compatível com a maioria dos sistemas de arquivos e paginação de memória virtual.
Cálculo da Ordem usada: M =Tamanho da Página/Tamanho do Elemento
Tamanho da Página: 4096 bytes.
Tamanho do Elemento: 16 bytes (8 bytes para a chave id + 8 bytes para o ponteiro/offset).
Resultado: 256, ou seja o Grau Final da árvore opera com Ordem 256.
Cada nó pode ter no máximo 256 filhos, armazenando no máximo 255 chaves.
Isso gera uma árvore muito "larga" e de baixa altura. Com apenas 3 níveis de altura, essa árvore pode indexar mais de 16 milhões de registros, garantindo acesso extremamente rápido.

Estratégia de Resolução de Overflow/Split:
O sistema utiliza a estratégia padrão de Split Proativo/Reativo:
Quando um nó atinge sua capacidade máxima (255 chaves) e uma nova inserção é requisitada.

Criamos a função dividirNo que funcionada da seguinte maneira:
O nó cheio é dividido em dois nós (o original e um novo irmão).
O conjunto de chaves é repartido igualmente entre eles.
A chave mediana ("elemento do meio") sofre Promoção
Se o nó for Folha: A cópia da mediana sobe para o pai (pois a folha deve manter todos os dados).
Se o nó for Interno: A mediana sobe para o pai e é removida do nó atual.
Se o pai também estiver cheio, o split se propaga para cima (podendo criar uma nova raiz).

#### Tempo de criação dos índices em memória

Foram realizadas três execuções consecutivas do programa, medindo o tempo de criação
dos índices em memória (hash para pedidos e árvore B+ para produtos).

| Estrutura                       | Execução 1 (s) | Execução 2 (s) | Execução 3 (s) | Média (s) |
| ------------------------------- | -------------- | -------------- | -------------- | --------- |
| Hash em memória (Pedidos)       | 0,037063       | 0,037657       | 0,038664       | 0,037795  |
| Árvore B+ em memória (Produtos) | 0,004468       | 0,004333       | 0,003794       | 0,004198  |

Para avaliar o custo de criação dos índices em memória, o programa foi executado três vezes medindo o tempo para construir a tabela hash de pedidos (95.899 registros indexados) e a árvore B+ de produtos. A tabela acima mostra os tempos individuais e a média das execuções. Observa-se que a criação do índice hash leva em torno de 0,0378 segundos, enquanto a criação da árvore B+ leva aproximadamente 0,0042 segundos. Esses valores são coerentes com o tamanho das estruturas: a hash indexa um conjunto bem maior de registros (pedidos), enquanto a árvore B+ é construída sobre um conjunto menor (produtos).

### Comparação de tempo de consulta – Produtos

Foram realizadas 5 consultas para diferentes produtos, comparando o tempo
de busca usando o índice de arquivo (`.idx`) e o índice em memória (árvore B+).

| #   | ID do Produto       | Tempo índice de arquivo (s) | Tempo árvore B+ (s) |
| --- | ------------------- | --------------------------- | ------------------- |
| 1   | 2501331816804253948 | 0,000071                    | 0,000020            |
| 2   | 2537782512956997930 | 0,000066                    | 0,000018            |
| 3   | 2539957035806490883 | 0,000063                    | 0,000028            |
| 4   | 2540059984184476519 | 0,000085                    | 0,000035            |
| 5   | 2541962442884252323 | 0,000043                    | 0,000023            |

**Médias:**

- Índice de arquivo (produtos): **0,0000656 s**
- Árvore B+ em memória (produtos): **0,0000248 s**

Para o conjunto de consultas em produtos, foram selecionados 5 IDs distintos e, para cada um, mediu-se o tempo de busca utilizando o índice em arquivo (produtos.idx) e a árvore B+ em memória. Os tempos individuais estão apresentados na tabela acima. A média das execuções mostra que a busca com índice em arquivo levou aproximadamente 0,000066 segundos, enquanto a mesma consulta utilizando a árvore B+ em memória levou cerca de 0,000025 segundos. Ou seja, para esse cenário, a consulta via árvore B+ foi em torno de 2,6 vezes mais rápida do que a consulta baseada no índice armazenado em arquivo. Isso é coerente com o fato de que, na árvore B+, toda a navegação e localização do offset ocorre em memória, evitando acessos adicionais ao arquivo de índice.

Na prática, isso ilustra a vantagem de manter estruturas de índice em memória para consultas intensivas: mesmo que ambos os métodos usem busca “guiada” (não varrem o arquivo inteiro), o custo de percorrer a B+ em memória é menor do que ler e processar o índice em disco.

### Tempo de criação dos índices em memória

Foram realizadas três execuções consecutivas do programa, medindo o tempo de criação
dos índices em memória (hash para pedidos e árvore B+ para produtos).

| Estrutura                       | Execução 1 (s) | Execução 2 (s) | Execução 3 (s) | Média (s) |
| ------------------------------- | -------------- | -------------- | -------------- | --------- |
| Hash em memória (Pedidos)       | 0,037063       | 0,037657       | 0,038664       | 0,037795  |
| Árvore B+ em memória (Produtos) | 0,004468       | 0,004333       | 0,003794       | 0,004198  |

### Tempo de consulta – Produtos (busca por ID)

Foram realizadas cinco consultas a produtos específicos, comparando o uso do índice de arquivo
com a árvore B+ em memória.

| Estrutura                      | Consulta 1 (s) | Consulta 2 (s) | Consulta 3 (s) | Consulta 4 (s) | Consulta 5 (s) | Média (s) |
| ------------------------------ | -------------- | -------------- | -------------- | -------------- | -------------- | --------- |
| Índice de arquivo (Produto)    | 0,000071       | 0,000066       | 0,000063       | 0,000085       | 0,000043       | 0,000066  |
| Árvore B+ em memória (Produto) | 0,000020       | 0,000018       | 0,000028       | 0,000035       | 0,000023       | 0,000025  |

### Tempo de consulta – Pedidos

Foram realizadas consultas por ID de pedido (usando índice de arquivo) e por data
(usando o índice hash em memória).

#### Busca por ID (índice de arquivo)

| Estrutura                         | Consulta 1 (s) | Consulta 2 (s) | Consulta 3 (s) | Consulta 4 (s) | Média (s) |
| --------------------------------- | -------------- | -------------- | -------------- | -------------- | --------- |
| Índice de arquivo (Pedido por ID) | 0,000071       | 0,000056       | 0,000157       | 0,000057       | 0,000085  |

#### Busca por data (índice hash em memória)

Consultas pela data **01/12/2021**:

| Estrutura                                     | Consulta 1 (s) | Consulta 2 (s) | Consulta 3 (s) | Média (s) |
| --------------------------------------------- | -------------- | -------------- | -------------- | --------- |
| Hash em memória (Pedidos por data 01/12/2021) | 0,000387       | 0,000397       | 0,000470       | 0,000418  |

Consulta pela data **30/11/2025** (bucket com 1 pedido):

| Estrutura                                     | Consulta única (s) |
| --------------------------------------------- | ------------------ |
| Hash em memória (Pedidos por data 30/11/2025) | 0,000137           |

Para o arquivo de pedidos, medimos o tempo de duas operações:

Pesquisa binária por ID de pedido utilizando o índice de arquivo de pedidos (pesquisa_com_indice_pedido);

Pesquisa por data utilizando o índice hash em memória (search_by_date), que retorna todos os pedidos daquela data.

Foram realizadas quatro execuções. Nas três primeiras, usamos a data 01/12/2021, que possui 177 pedidos no mesmo bucket; na última, usamos a data 30/11/2025, com apenas 1 pedido.

Os resultados mostraram que:

A busca por ID via índice de arquivo foi muito rápida, com tempo médio de aproximadamente 0,000085 s (85 microssegundos) por consulta.

A busca por data via hash em memória levou, em média, cerca de 0,00035 s (350 microssegundos), ficando em torno de 4 vezes mais lenta do que a busca por ID, nas condições testadas.

Considerando apenas a data com 177 pedidos, a média da busca por data via hash subiu para cerca de 0,00042 s, pois o algoritmo precisa percorrer e imprimir todos os registros do bucket.

É importante observar que, no nosso experimento, o tempo da função de hash inclui não só a busca na estrutura em memória, mas também o custo de percorrer e exibir todos os pedidos encontrados na tela. Como para a data 01/12/2021 existem 177 registros, o custo de E/S (impressão) impacta bastante o tempo total.

Mesmo assim, ambos os métodos respondem em menos de 1 milissegundo nas consultas realizadas, mostrando que tanto o índice em arquivo quanto o índice em memória (hash) são eficientes para o volume de dados do trabalho. A principal diferença é semântica:

o índice de arquivo foi usado para localizar um único pedido específico por ID;

o hash em memória foi usado para listar todos os pedidos de uma determinada data, o que naturalmente envolve mais processamento e E/S quando a data concentra muitos registros.
