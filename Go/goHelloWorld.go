package main

import( 
	"fmt"
	"math/rand"
	"math"
)

func add(x, y int) int{
	return x+y
}

func swap(x,y string) (string, string){
	return y,x
}

func main() {

	fmt.Println("Hello world")
	fmt.Println("Here is a random number for you!",
		rand.Intn(10), "\b!")

	fmt.Printf("Printing: %g!\n",
		math.Nextafter(2,3))
	fmt.Println("Pi is", math.Pi)

	fmt.Println("2+3=", add(2,3))

	w,t := swap("hello", "world")
	fmt.Println(w,t)
}
