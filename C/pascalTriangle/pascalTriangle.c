#include<stdio.h>

int a[9];
int main(){
	a[5] = 1; 
	pa();

}

void pa(){
	int i;
	for(i=0;i<9;i++)
		printf("%i", a[i]);
	printf("\n");
}
