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
struct invert list[100];
//***************/

int hash(char s[]){     //simple hash function
        return (int)s%n;
}

void *mapThreadEnter(void* threadid){

        int t = (int)threadid;  //MAP thread saying hello
        printf("MAP: %d\n", t);

        char buffer[ SIZE ];    //initializations
        char* last;
        //--------------------------------------
        char* s = (char*)calloc(1, sizeof(char));
        char d[10];
        strcpy(s,"");
        strcat(s,"foo");
        sprintf(d, "%d", t);
        strcat(s,d);
        strcat(s,".txt");
        ss[t] = (char*)calloc(1, 10*sizeof(char));
        strcpy(ss[t], s);
        //printf("%s",s);       //code to create name of foox.txt file
        //--------------------------------------

        FILE* input = fopen( s, "r" );
        if(input == NULL){
                fprintf(stderr, "Can't open file %s\n", s);
        }
        else{
                int i;
                while( fgets(buffer, SIZE, input) != NULL ){
                        sem_wait(&lock1);
                        strcpy(Rbuffer[hash(buffer)],buffer);
                                //copy operation is locked
                                //because Rbuffer is global
                        sem_post(&lock1);

                                //      last = strtok(buffer," "); //full string tokenizer
                                //      while(last != NULL){
                                //      printf("%s", last);
                                //      last = strtok(NULL," ");

                }

                if(ferror(input)){//in case there is an error, catch it
                       perror("Error with the file.");
                }

                fclose(input);  //close the opened file

        }

        printf("--MAP EXIT: %i\n", t);
        sem_wait(&lock2);
        writer--;               //say goodbye, decrement total maps, exit
        sem_post(&lock2);
        pthread_exit(NULL);
}

void *reduceThreadEnter(void* threadid)
{
        int t = (int)threadid;  //REDUCE thread says hello
        printf("REDUCE: %d\n", t);
        while(writer){
                sem_wait(&lock2);//count is locked
                count++;
                if(count==1)
                        sem_wait(&lock1);//if one reader, lock writers
                //sem_post(&lock2);//count unlocked

                int i = 0;
                int tf=1;//no boolean support

                if(listCount>0){//for every entry in the list, check if equal
                         for(i=0;i<listCount;i++){
                                   if(strcmp(list[i].word, Rbuffer[t])){
                                              list[i].num++;
//                                            list[i].line[list[i].num];
                                              tf=0;
                                    }
                         }
                 }
                 if(tf){        //if the word is new, make a new entry for it.
                         list[t].word = Rbuffer[t];
                         list[t].file = ss[t];
                         list[t].num = 0;
                         listCount++;
//                       list[t].line[list[i].num++];// = cu;
                }

                printf("Strings: _%s_%s_%s_\n", Rbuffer[t], list[t].word, list[t].file);

                //sem_wait(&lock2);//count is locked
                count--;
                if(count==0)
                        sem_post(&lock1);//if no readers, unlock a writer
                sem_post(&lock2);//count is unlocked
        }
        printf("--REDUCE EXIT: %i\n", t);
        pthread_exit(NULL);     //say goodbye
}

int main(){

        int i;

        printf("Enter the number of Map threads.\n");
        scanf("%d",&m);
        printf("Enter the number of Reduce threads.\n");
        scanf("%d",&n);

        pthread_t mapThreads[m];
        pthread_t reduceThreads[n];
        sem_init(&lock1, 0, 1);
        sem_init(&lock2, 0, 1);
        ss[100] = (char*)calloc(1, 1000*sizeof(char));

        int tcheck;

        for(i=0;i<m;i++){       //create m mapper threads
                printf("MThread: %d\n",i+1);
                tcheck = pthread_create(&mapThreads[i], NULL,
                                        mapThreadEnter, (void *)i);
                if (tcheck){
                        printf("ERROR, unable to create thread %d\n",tcheck);
                        exit(-1);
                }
        }

        for(i=0;i<n;i++){       //create n reducer threads
                printf("RThread: %d\n",i+1);
                tcheck = pthread_create(&reduceThreads[i], NULL,
                                        reduceThreadEnter, (void *)i);
                if (tcheck){
                        printf("ERROR, unable to create thread %d\n",tcheck);
                        exit(-1);
                }
        }

        for(i=0;i<m;i++){       //wait for all of the mappers to finish
               pthread_join(mapThreads[i], NULL);
        }

        for(i=0;i<n;i++){       //wait for all of the reducers to finish
                pthread_join(reduceThreads[i], NULL);
        }
return 0;
}
