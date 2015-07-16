#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAXSIZE 299//max number of chars in the line

	char a[MAXSIZE];
	char b[MAXSIZE];
	int c[MAXSIZE][MAXSIZE];
	int d[MAXSIZE][MAXSIZE];
	int count;
	
char max(char a, char b){
	if(a>b) return a;
	return b;
}

void printAll(int q){
	if(q==0){
		int x,y;
		for(x=0;x<MAXSIZE;x++){
			for(y=0;y<MAXSIZE;y++){
				printf("%i ",c[x][y]);
			}
		printf("\n");
		}
	}
	if(q==1){
		int x,y;
		for(x=0;x<MAXSIZE;x++){
			for(y=0;y<MAXSIZE;y++){
				printf("%i ",d[x][y]);
			}
		printf("\n");
		}
	}
	printf("%s----------------%s\n\n",a,b);	
}
void fillArray(){
	int x,y;
	for(x=1;x<MAXSIZE;x++){
		for(y=1;y<MAXSIZE;y++){
			if(a[x]==b[y]){
				c[x][y] = c[x-1][y-1]+1;
				d[x][y] = 1;
			}
			else if(c[x-1][y] >= c[x][y-1]){
				c[x][y] = c[x-1][y];
				d[x][y] = 2;
			}
			else{
				c[x][y] = c[x][y-1];
				d[x][y] = 3;
			}
		}
	}
}
void recursiveBacktrack(int x, int y){
	if(x==0 || y==0){
		printf("%c",a[x]);
		count++;
		return;
	}
	else
	if(d[x][y]==1){
			recursiveBacktrack(x-1,y-1);//diagonal
			if(a[x]!='\0'){
				printf("%c",a[x]);
				count++;
			}
	}
	else if(d[x][y]==2){		
			recursiveBacktrack(x-1,y);//left
	}
	else if(d[x][y]==3){		
			recursiveBacktrack(x,y-1);//up
	}
	else{
			printf("%i %i %i There's been a problem", x,y,d[x][y]);
	} 
}

int main (){
	time_t start, stop;
	time(&start);
	FILE *seq;
	FILE *smallseq;

	seq = fopen("h.txt", "r");
	smallseq = fopen("t.txt", "r");

    if (seq == 0){
        perror("Can't open input file 1\n");
        exit(-1);
    }
    else if (smallseq == 0){
        perror("Can't open input file 2\n");
        exit(-1);
    }
    else{
		int i;
		count=0;
		for(i=0;i<3;i++){
			fscanf(seq, "%s", &a);
			fscanf(smallseq, "%s", &b);

			//----initializing the array to 0
			int j,k;	//only need to do the first row/col
			for(j=0;j<MAXSIZE;j++)
				c[j][0]=0;
			for(k=0;k<MAXSIZE;k++)
				c[0][k]=0;
				
			//----filling the array----------
				fillArray();
			//-------------------------------
				printf("Line %i both docs:\n",i+1);
				printAll(3);
			//-------------------------------
			recursiveBacktrack(MAXSIZE-1,MAXSIZE-1);
			printf("\nLength of LCS: %i\n\n",count);
			count=0;
		}//end for to 3
    }//end else(file exists)
	time(&stop);
	printf("Finished in about %f seconds. \n", difftime(stop, start));
	return 0;

}//end main
