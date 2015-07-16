/*************
Patrick Beagan
27529823
http://stackoverflow.com/questions/16620779/printing-tokenized-data-from-file-in-c
http://stackoverflow.com/questions/4142745/initialize-a-string-in-c-to-empty-string
https://www.cs.bu.edu/teaching/cpp/string/array-vs-ptr/
http://www.csc.villanova.edu/~mdamian/threads/posixsem.html#init
*************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#define SIZE 10

struct invert{
        char* word;
        char* file;
        int line[100];
        int num;
};

//Globals
//**************/
int m,n;
//char Rbuffer[100][SIZE];
char Rbuffer[100][SIZE];
char* ss[100];
sem_t lock1;
sem_t lock2;
int writer;
int count=0;
int listCount = 0;
//***************/

int main(){

        int i;
	char* s;

        char buffer[ SIZE ];    //initializations

	printf("Enter the name of the file.");
	scanf("%s",s);

        FILE* input = fopen( "README.txt", "r" );
        if(input == NULL){
                fprintf(stderr, "Can't open file %s\n", s);
        }
        else{
                int i;
                while( fgets(buffer, SIZE, input) != NULL ){
			printf("%s", buffer);
                }

                if(ferror(input)){//in case there is an error, catch it
                       perror("Error with the file.");
                }

                fclose(input);  //close the opened file

        }

        printf("--MAP EXIT: \n");

return 0;
}
