# Trabalho-Algoritmos-parte-2

# Indíces Hash:
Aplicamos uma indexação por hash no campo de data da tabela de pedidos. As colisões em data iguais são usadas para definir os buckets por lista encadeada, assim pode ser feito de forma muito eficiente uma consulta mostrando todos os pedido em uma data específica. Função de hash = (ano*31 + mes*31 + dia) % 96001(numero primo mais proximo do num de registros)
