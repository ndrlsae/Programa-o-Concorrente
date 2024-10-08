#
Esse repositório contém uma implementação do padrão leitores e escritores com prioridade de escrita, utilzando sincronização de threads.

Os arquivos list_int.c e list_int.c foram extraídos do livro An Introduction to Parallel Programming, Peter Pacheco, Morgan Kaufmann, 2011 (cap4) e implementam o TAD lista.

Os arquivos wrlock.c e wrlock.h são parte da minha implementação do padrão leitores escritores com prioridade de escrita. 
O wrlock.h é incluído no código main_wrlock.c onde utilizei o padrão.

Esse código main possui um código tarefa que é executado pelas threads, com o fim de exemplificar o uso do programa.
Essa tarefa consiste na inserção, visualização e deleção em uma lista que é compartilhada por todas as threads, sendo que inserção e deleção são operações de escrita e portanto devem ser feitas em seções críticas, além de terem prioridade pela especificação do problema.
Além disso criei uma função demorada (func_demorada()) para ocupar o tempo das leituras e escritas no código e ajudar na visualização da execução do código.

Os arquivos main_wrlock_print.c e wrlock_print.c são iguais aos arquivos main_wrlock.c e wrlock.c, porém, com várias linhas de printf adicionadas para conferir se o código está de fato realizando o esperado. Fiz isso para que houvesse a possibilidade de usar a implementação de maneira genérica, fora do contexto do exercício.

No diretório 'exemplos', há 5 arquivos output.txt, cada um deles é uma execução do programa com os parâmetros descritos no cabeçalho.

## Compilação

Para compilar o programa utilize o seguinte comando:
```bash
gcc -o wrlock main_wrlock.c wrlock.c list_int.c -Wall
```
ou para versão com prints

gcc -o wrlock main_wrlock_print.c wrlock_print.c list_int.c -Wall
## Execução

Depois da compilação o programa deve ser executado dessa maneira:

```bash
./wrlock <número de threads>
```

## Atividade 3

