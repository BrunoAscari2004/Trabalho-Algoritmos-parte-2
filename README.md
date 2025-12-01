# Trabalho-Algoritmos-parte-2

# Indíces Hash:
Aplicamos uma indexação por hash no campo de data da tabela de pedidos. As colisões em data iguais são usadas para definir os buckets por lista encadeada, assim pode ser feito de forma muito eficiente uma consulta mostrando todos os pedido em uma data específica. Função de hash = (ano*31 + mes*31 + dia) % 96001(numero primo mais proximo do num de registros)

#indice por arvore:
O código implementa uma  Árvore B+, pois na B+ os nós internos ficam menores (sem dados), permitindo um grau maior (fan-out) e menos acessos à memória para encontrar a folha. Além disso, facilita a varredura sequencial."

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
