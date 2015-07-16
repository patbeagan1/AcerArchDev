#include<stdio.h>

int main(){

//algorithm 1
	int a=1;
	int b=1;

	while(a<10000){
		printf("%i\n%i\n", a,b);
		a = a+b;
		b = a+b;
	}
//algorithm 2
	int x=1;
	int y=1;
	int z=0;
	while(z<10000){
		x=y;
		y=z;
		z = x+y;
		printf("%i\n", z);
	}
}
