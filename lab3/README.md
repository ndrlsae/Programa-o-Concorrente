O objetivo deste programa é resolver multiplicação de matrizes de maneira concorrente e analisar o ganho de desempenho em comparação a uma implementação sequencial.

A pasta src contém os códigos utilizados para: 
- gerar matrizes NxM em um arquivo binário;
- multiplicar duas matrizes de maneira sequencial;
- multiplicar duas matrizes de maneira concorrente;
- além de um .h que contém as funções para marcar o tempo de execução de cada versão;

A pasta data contém um Markdown com três tabelas, cada uma referente a um tamanho de matriz com os valores de tempo encontrados nos experimentos. Além disso o código python usado para construir os gráficos que também estão na pasta e no arquivo analise.md, onde fazemos a análise de desempenho das funções sequencial e concorrente(variando o número de threads).

