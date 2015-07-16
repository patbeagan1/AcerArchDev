#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>

int main(int argc, char *argv[]){
//-------------------------------------	
	int i, count;
	FILE* fd;
	char* buf;
	char* fbl;
	int empty[64][2];
//--------------------------------------
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

	buf = (char*) calloc(16,1024);
	fbl = (char*) calloc(sizeof(char), 128);

	fread(fbl, sizeof(char), 128, fd);
	count=0;
	for(i=0;i<127;i++){
		if((int)fbl[i]==0)
			count++;
		printf("%i", fbl[i]);
	}
	printf("\n");
	//	fwrite(buf, 1024, sizeof(char), fd);
  
	//for(i=0;i<127;i++){
	//	fwrite(buf, 1024, sizeof(char), fd);
	//}

	fclose(fd);
	exit(1);
}
