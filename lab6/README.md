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
```bash
gcc -o wrlock main_wrlock_print.c wrlock_print.c list_int.c -Wall
```
## Execução

Depois da compilação o programa deve ser executado dessa maneira:

```bash
./wrlock <número de threads>
```

## Atividade 3
Nó código wrlock.c: além do padrão leitores e escritores básico, para cumprir o propósito da atividade, acrescentei uma nova variável de condição (q_write) que diz respeito à fila de escritores que se forma quando um escritor chega e não consegue acessar a lista. 
Essa variável será usada para barrar possíveis leitores que queiram ler da lista quando há escritor na fila. Como a prioridade é do escritor, um novo leitor agora só vai entrar se, além de não haver nenhum escritor escrevendo, também não houver nenhum escritor esperando para entrar. 
Além disso, quando um escritor termina, é importante que seja dado signal na fila de escritores antes do broadcast na fila de lleitores.

Nos códigos main_wrlock_print.c e wrlock_print.c: nesses códigos temos os prints que aparecerão nos outputs. As primeiras linhas serão o cabeçalho especificando os parâmetros da execução específica.
Ainda no main_wrlock_print.c temos prints antes e depois de toda iteração na função tarefa, indicando em qual thread essa iteração está acontecendo. Já em wrlock_print.c temos prints quando um escritor ou leitor é barrado, esses prints também indicam a razão de estar barrado, ou seja, informa quantos escritores já estão no sistema escrevendo ou esperando, e no caso de um escritor ser barrado, teremos também quantos leitores estão lendo naquele momento.

Podemos ir aos exemplos:

#output1.txt
nas linhas 9 a 14, conseguimos ver uma situação em que uma thread estava realizando uma escrita (thread 0: quero deletar), enquanto outra também queria (thread 1: quero deletar), mas a thread 1 ficou barrada pois havia 1 escritor escrevendo.
na linha 19 podemos ver uma situação em que a thread 0 quer ler mas não pode pois exitsem 2 escritores no sistema.
#output2.txt

#output3.txt

#output4.txt

#output5.txt






