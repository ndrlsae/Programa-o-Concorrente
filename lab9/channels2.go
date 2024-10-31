//introduz canais na aplicação Go
package main

import (
	"fmt"
)

func tarefa(str chan string) {
  var msg2 = ""
  msg2 = <- str
  fmt.Println(msg2)
  str <- "Oi Main, bom dia, tudo bem?"
  msg2 = <- str
  fmt.Println(msg2)
  str <- "Certo, entendido"
  str <- ""
	fmt.Printf("finalizando\n")
}

func main() {
	var msg = ""
	str := make(chan string)
	
  go tarefa(str)
	str <- "Olá, Goroutine, bom dia!"
  msg = <-str //bloqueio, só saio daqui quando tiver algo no canal
	fmt.Println(msg)
  str <- "Tudo bem! Vou terminar tá?"
  msg = <- str
  fmt.Println(msg)
  msg = <-str //apenas pra aguardar a thread finalizar
  fmt.Printf("finalizando\n")
}
