#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>
using namespace std;

typedef struct inode{
		char name[8];//file name
		int size;
		int blockPointers[8];
		int used;
} inode;

//-------------------------------------	
	int i,j,k, count;
	FILE* fd;
	char* buf;
	char* buf2;
	inode inodeptr;
	inode tmp;
	char* fbl;
	int empty[64][2];
//--------------------------------------

void printSys(){
	for(i=0;i<128;i++){
		printf("%i", fbl[i]);
	}
	printf("\n");
}

int check(){
	for(k=0;k<inodeptr.size;k++){
			if(count==0)cout<<inodeptr.blockPointers[k]<<" "<<endl;//show which nodes point to which blocks

					if(inodeptr.blockPointers[k]>count 
					&& inodeptr.blockPointers[k]<128 
					&& fbl[inodeptr.blockPointers[k]]!=0){
						
						cout<<inodeptr.blockPointers[k]<<" "<<count<<endl;
						fbl[inodeptr.blockPointers[k]]=7;//7 and 9 to show changes
						fbl[count]=9;
						
						
						//fseek(fd, inodeptr.blockPointers[k]*1024, SEEK_SET);//reading the mismatched blocks
						//fread(&buf, sizeof(char), 1024, fd);
						//fseek(fd, count*1024, SEEK_SET);
						//fread(&buf2, sizeof(char), 1024, fd);
						
						//fseek(fd, inodeptr.blockPointers[k]*1024, SEEK_SET);//swapping the mismatched blocks
						//fwrite(buf2, sizeof(char), 1024, fd);
						//fseek(fd, count*1024, SEEK_SET);
						//fwrite(buf, sizeof(char), 1024, fd);
						
						rewind(fd);
						fwrite(fbl, sizeof(char), 128, fd);
						
						inodeptr.blockPointers[k]=count;

						fseek(fd, j*48, SEEK_CUR);
						fwrite(&inodeptr, sizeof(char), 128, fd);
						
						
						
						return 0;
					}
	}
	return -1;
}

int main(int argc, char *argv[]){
	if (argc == 1 ){
		fprintf(stderr,"usage: %s <diskFileName> \n",argv[0]);
		exit(0);
	}
	
//---------------------------------------
	printf("Opening file: %s\n", argv[1]);
	fd = fopen( argv[1], "r+" );
	if(fd == NULL){
		fprintf(stderr, "The input file was not found.\n");
		exit(-1);
	}
	printf("SUCCESS\n");
	
//----------------------------------------
	printf("DEFRAGGING...\n");

	buf = (char*) calloc(sizeof(char)-1,1024);
	fbl = (char*) calloc(sizeof(char), 128);

	fread(fbl, sizeof(char), 128, fd);	

	printSys();

//---------------------------------------

	for(count=0;count<128;count++){//down the list
		for(j=0;j<16;j++){//search each inode each time
			fread(&inodeptr, sizeof(char), 48, fd);
			//if(count==0){for(k=0;k<inodeptr.size;k++){cout<<inodeptr.blockPointers[k]<<" ";}cout<<endl;}
			if((int)fbl[count]==0){
				check();
			}
		}
		fseek(fd, 128, SEEK_SET);
		printSys();
	}

//---------------------------------------

	printSys();
	fclose(fd);
	exit(1);
}
