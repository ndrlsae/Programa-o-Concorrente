# Lab2 - Programação Concorrente

## Descrição 
Esse projeto tem como objetivo a introdução ao paralelismo de dados utilizando a linguagem C e a biblioteca Pthreads.

O código vector.c recebe um inteiro N e o nome para um arquivo binário que será criado contendo na primeira linha no valor de N(int), na segunda e terceira linha dois vetores float "aleatórios" de dimensão N e na última linha o produto interno desses dois vetores(double) calculado de maneira sequencial. Esse arquivo binário será entrada do próximo código prod_int.c .

O código prod_int.c recebe um arquivo binário e um inteiro M, esse código calcula, de maneira concorrente, o produto interno(float) dos vetores no arquivo binário utilizando M threads (balanceadas) e compara com o valor do arquivo binário por meio da variação relativa.

O único resultado encontrado tanto pro erro absoluto quando pra variação relativa foi 0 absoluto em todos os testes, mesmo alternando entre float e double. Printando os valores separadamente é possível ver que são iguais até pelo menos a 2ª casa decimal, mas nas casas seguintes os valores variam conforme a quantidade de threads. Acredito que na subtração da variação relativa o valor já fica tão pequeno que a precisão já considera como 0 absoluto e por isso esses resultados.

