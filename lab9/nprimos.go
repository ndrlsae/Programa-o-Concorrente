package main
import (
  "fmt"
  "math"
)

const N = 100
const M = 17

func ehPrimo(n int ) bool{
  if (n<=1) {return false}
  if (n==2) {return true}
  if (n%2==0) {return false}
  for i:=3; i<int(math.Sqrt(float64(n)))+1; i+=2{
    if(n%i==0) {return false}}
  return true}

func conta_primos(num chan int, canal chan int){
  var i = 0
  for{
    i = <-num
    if(ehPrimo(i)){
      canal<-1
    } else {canal<-0  
    }
    }
  }


func main(){
  var total = 0

  numero := make(chan int)
  ehprimo := make(chan int)

  for j := 0; j<M; j++ {
    go conta_primos(numero, ehprimo)
  }

  for i := 1; i < N; i++ {
    numero <- i

    j := <- ehprimo
    if j==1 {
    total = total + 1
    }  
  }
  close(numero)
  close(ehprimo)

  fmt.Println("Total =", total)  
  }



