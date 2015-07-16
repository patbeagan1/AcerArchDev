/* create a file  to act as a disk  and format the file system residing on the disk */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstdlib>

int
main(int argc, char *argv[])
{
  int i;
  FILE* fd;
  char *buf;

  if (argc == 1 ){
    fprintf(stderr,"usage: %s <diskFileName> \n",argv[0]);
    exit(0);
  }

  printf("This file will act as a dummy disk and will hold your filesystem\n");

  fd = fopen( argv[1], "w" );
  if(fd == NULL){
		fprintf(stderr, "The input file was not found. Looking for a file named \"input.txt\".\n");
  }
  printf("Formatting your filesystem...\n");

  buf = (char *) calloc(1024,sizeof(char));
  
  buf[0]=1; 
		fwrite(buf, 1024, sizeof(char), fd);
  buf[0]=0;
  for(i=0;i<127;i++){
		fwrite(buf, 1024, sizeof(char), fd);
  }

  fclose(fd);
  exit(1);

}
