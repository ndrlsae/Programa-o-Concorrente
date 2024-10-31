Esse código tem como objetivo praticar o uso de troca de mensagens na linguagem Go.

O código channels2.go é referente a Atividade 2 e implementa um diálogo ordenado da main com uma goroutine

Os códigos nprimos.go e nprimos2.go resolvem a Atividade 5, imprimindo a quantidade de primos de uma sequência de 1 até N, contados por M goroutines. No nprimos.go N = 100 e M = 17, mas, para verificar a corretude implementei também nprimos2.go onde N e M são inseridos no terminal, facilitando a testagem do código.

Para rodar

´´´bash
go run nprimos.go
#ou
go run nprimos.go <range da lista> <número de threads>

