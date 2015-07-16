#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#define USED 1
#define FREE 0
#define GREEN 	"\x1b[32m"
#define YELLOW 	"\x1b[33m"
#define RED		"\x1b[31m"
#define RESET	"\x1b[0m"


using namespace std;

typedef struct inode{
		char name[8];//file name
		int size;
		int blockPointers[8];
		int used;
} inode;

//*******GLOBALS****************
FILE* input;
FILE* fptr;
char* freeBlockList;
char* blockBuffer;
char* holder;
inode temp;
char* last;
char buffer[30];
char* args[3];
int i,j,fbptr;
char frag;
//******************************

int FileSystem(char diskName[16]){
	// open the file with the above name
		fptr = fopen( diskName, "r+" );
		if(fptr == NULL){ 
			printf("file: ...%s...was not found. I'll try making a new file by that name. Please restart the program after.\n", diskName);
			const char* path = "./create_fs";
			execl(path, path, diskName, (char*)0);
			cout<<"Please compile the create_fs.cc file."<<endl;
			return -1;
		}
	// this file will act as the "disk" for your file system
		cout<<"File "<<diskName<<" successfully opened"<<endl;
		return 0;
}

int creater(char name[8], int size){
	//create a file with this name and this size
    // high level pseudo code for creating a new file

    // Step 1: Check to see if we have sufficient free space on disk by
    // reading in the free block list. To do this:
    // Move the file pointer to the start of the disk file.
    // Read the first 128 bytes (the free/in-use block information)
    // Scan the list to make sure you have sufficient free blocks to
    // allocate a new file of this size
	
		cout<<"P-"<<ftell(fptr)<<"\tChecking that there is space on the disk."<<endl;
		
		int i, count=0;//, max=0;
		rewind(fptr);
		fread(freeBlockList, sizeof(char), 128, fptr);
		
		cout<<"\tFBL: ";
		for(i=0;i<128;i++){
			cout<<(int)freeBlockList[i];
			if(freeBlockList[i]==0){
				count++;
			}
			if(i==63)cout<<endl<<"\t     ";
		}
		cout<<endl;
		if(count>=size){
			cout<<"\tThere is. Attempting to create the file..."<<endl;
		}
		else{
			cout<<"\tNO ROOM, ABORTING FILE CREATION"<<endl;
			return -1;
		}
    // Step 2: we look for a free inode on disk
    // Read in an inode
    // Check the "used" field to see if it is free
    // If not, repeat the above two steps until you find a free inode
    // Set the "used" field to 1
    // Copy the filename to the "name" field
    // Copy the file size (in units of blocks) to the "size" field
		int iNodeLoc;
		if(fseek(fptr, 128, SEEK_SET)!=0){
			cout<<"File error.";
			exit(-1);
		}
		for(i=0;i<16;i++){
			fread(&temp, sizeof(char), 48, fptr);
			if(temp.used==FREE){
				temp.used=USED;
				iNodeLoc = i;
				break;
			}
		}
		strcpy(temp.name, name);

		temp.size = size;
		cout<<"\t\tName: "<<temp.name<<endl//*(int*)temp.name<<endl
			<<"\t\tSize: "<<temp.size<<endl;
		
    // Step 3: Allocate data blocks to the file
    // for(i=0;i<size;i++)
    // Scan the block list that you read in Step 1 for a free block
    // Once you find a free block, mark it as in-use (Set it to 1)
    // Set the blockPointer[i] field in the inode to this block number.
    // end for
		int j;
		if(frag!='y')fbptr=0;
		for(i=0;i<size;i++){
			for(j=fbptr;j<128;j++){
				if(freeBlockList[j]==0){
					freeBlockList[j]=1;
					temp.blockPointers[i]=j;
					fbptr=j;
					break;
				}
			}
		}

    // Step 4: Write out the inode and free block list to disk
    // Move the file pointer to the start of the file 
    // Write out the 128 byte free block list
    // Move the file pointer to the position on disk where this inode was stored
    // Write out the inode
		cout<<"P-"<<ftell(fptr);
		rewind(fptr);
		fwrite(freeBlockList, 128, sizeof(char), fptr);
		fseek(fptr, 128+48*iNodeLoc, SEEK_SET);
		fwrite(&temp, 48, sizeof(char), fptr);
		return 0;//SUCCESS
} 	// End Create

int deleter(char name[8]){
	// Delete the file with this name

    // Step 1: Locate the inode for this file
    // Move the file pointer to the 1st inode (129th byte)
    // Read in an inode
    // If the inode is free, repeat above step.
    // If the inode is in use, check if the "name" field in the
    // inode matches the file we want to delete. If not, read the next
    // inode and repeat
		int i, iNodeLoc=-1;
		
		fseek(fptr, 128, SEEK_SET);
		for(i=0;i<16;i++){
			fread(&temp, sizeof(char), 48, fptr);
			if(temp.used==USED){
				if(strcmp(temp.name, name)==0){
					iNodeLoc = i;
					break;
				}
			}
		}
		if(iNodeLoc==-1){
			cout<<"\tThe file in question was not found."<<endl;
			return -1;
		}
    // Step 2: free blocks of the file being deleted
    // Read in the 128 byte free block list (move file pointer to start
    // of the disk and read in 128 bytes)
    // Free each block listed in the blockPointer fields as follows:
    // for(i=0;i< inode.size; i++) 
    // freeblockList[ inode.blockPointer[i] ] = 0;
		rewind(fptr);
		fread(freeBlockList, sizeof(char), 128, fptr);
		
		for(i=0;i< temp.size; i++){ 
			freeBlockList[ temp.blockPointers[i] ] = 0;
		}
		
    // Step 3: mark inode as free
    // Set the "used" field to 0.
		temp.used = FREE;
		
    // Step 4: Write out the inode and free block list to disk
    // Move the file pointer to the start of the file 
    // Write out the 128 byte free block list
    // Move the file pointer to the position on disk where this inode was stored
    // Write out the inode
		cout<<"P-"<<ftell(fptr);
		rewind(fptr);
		fwrite(freeBlockList, 128, sizeof(char), fptr);
		fseek(fptr, 128+48*iNodeLoc, SEEK_SET);
		fwrite(&temp, 48, sizeof(char), fptr);
		return 0;
} // End Delete

int ls(){ 
	// List names of all files on disk

    // Step 1: read in each inode and print
    // Move file pointer to the position of the 1st inode (129th byte)
		fseek(fptr, 128, SEEK_SET);
    
    // for(i=0;i<16;i++)
    // Read in an inode
    // If the inode is in-use
    // print the "name" and "size" fields from the inode
    // end for
		j=0;
		for(i=0;i<16;i++){
			fread(&temp, sizeof(char), 48, fptr);
				if(temp.used==USED){
					//if(j++%4==0) cout<<endl<<"\t";
					cout<<"\t"<<temp.name<<"   \t@"<<i<<"\tSIZE:"<<temp.size<<endl;
				}
		}
		return 0;
} // End ls

int reader(char name[8], int blockNum, char buf[1024]){
    // read this block from this file

    // Step 1: locate the inode for this file
    // Move file pointer to the position of the 1st inode (129th byte)
    // Read in an inode
    // If the inode is in use, compare the "name" field with the above file
    // If the file names don't match, repeat
	int i, addr;
		
		fseek(fptr, 128, SEEK_SET);
		for(i=0;i<16;i++){
			fread(&temp, sizeof(char), 48, fptr);
			if(temp.used==USED){
				if(strcmp(temp.name, name)==0){
					break;
				}
			}
		}
    // Step 2: Read in the specified block
    // Check that blockNum < inode.size, else flag an error
    // Get the disk address of the specified block
    // That is, addr = inode.blockPointer[blockNum]
    // Move the file pointer to the block location (i.e., to byte #
    // addr*1024 in the file)
		if(blockNum >= temp.size){
			cout<<"That exceeds the size of the file."<<endl;
			return -1;
		}
		addr = temp.blockPointers[blockNum];
		fseek(fptr, (addr)*1024, SEEK_SET);
		
    // Read in the block => Read in 1024 bytes from this location
    // into the buffer "buf"
    	fread(buf, sizeof(char), 1024, fptr);
    	cout<<"\tThe first 20 bytes of "<<temp.name<<endl<<"\tare: ";
    	for(j=0;j<20;j++){
			cout<<buf[j];
		}
		cout<<endl;
		return 0;
} // End read


int writer(char name[8], int blockNum, char buf[1024]){
	// write this block to this file

    // Step 1: locate the inode for this file
    // Move file pointer to the position of the 1st inode (129th byte)
    // Read in a inode
    // If the inode is in use, compare the "name" field with the above file
    // If the file names don't match, repeat
	int i, addr;
		
		fseek(fptr, 128, SEEK_SET);
		for(i=0;i<16;i++){
			fread(&temp, sizeof(char), 48, fptr);
			if(temp.used==USED){
				if(strcmp(temp.name, name)==0){
					break;
				}
			}
		}
    // Step 2: Write to the specified block
    // Check that blockNum < inode.size, else flag an error
    // Get the disk address of the specified block
    // That is, addr = inode.blockPointer[blockNum]
    // Move the file pointer to the block location (i.e., byte # addr*1024)
		if(blockNum >= temp.size){
			cout<<"That exceeds the size of the file."<<endl;
			return -1;
		}
		addr = temp.blockPointers[blockNum];
		cout<<"BLK-"<<addr;
		fseek(fptr, addr*1024, SEEK_SET);
		
    // Write the block! => Write 1024 bytes from the buffer "buff" to 
    // this location
		
		fread(buf, sizeof(char), 1024, fptr);
    	cout<<"\tRewrote the first 20 bytes of "<<temp.name<<endl<<"\tfrom: ";
		for(j=0;j<20;j++){
			cout<<buf[j];
		}
		cout<<endl<<"\t  to: ";
		for(j=0;j<20;j++){
			buf[j]='a';
			cout<<buf[j];
		}

		cout<<endl;
		fseek(fptr, -1024, SEEK_CUR);
		fwrite(buf, 1024, sizeof(char), fptr);
		return 0;
} // end write
  
int main(){
	cout<<endl<<"About to read the input file..."<<endl;
	input = fopen( "input.txt", "r+" );
    if(input == NULL){
		fprintf(stderr, "The input file was not found. Looking for a file named \"input.txt\".\n");
    }
    cout<<"The file was opened correctly."<<endl;
    
    cout<<RED"Do you want the disk to fragment(y) or no(n)?"RESET<<endl;
    cin>>frag;
    if(frag=='y')
		cout<<"the disk will fragment."<<endl;
	else
		cout<<"the disk will NOT fragment"<<endl;
	fbptr = 0;
    freeBlockList = (char*)malloc(128*sizeof(char));
    blockBuffer = (char*)malloc(1024*sizeof(char));


	while( fgets(buffer, 30, input) != NULL ){
		//j++;
		//cout<<"looking at line "<<j<<endl;
        //first use a string tokenizer to parse the line and create an arg list.
        last = strtok(buffer," ");
		for(i=0; i<3 && last != NULL; i++){
			args[i] = last;
			last = strtok(NULL," ");
			//cout<<last<<endl;
		}
		//then switch on the first arg, which determines the function that we go to.
		int result = -1;
		//cout<<args[0]<<endl;
		//cout<<args[2];
		int a;
		switch(*args[0]){
		
			case 'C':	a = atoi(args[2]);
						cout<<YELLOW"Creating "RESET<<args[1]<<"..."<<endl; 
						result = creater(args[1], a);
						break;
			case 'W':	
						a = atoi(args[2]);
						cout<<YELLOW"Writing "RESET<<args[1]<<" @"<<a<<"..."<<endl; 
						result = writer(args[1], a, blockBuffer);
						break;
			case 'R':	a = atoi(args[2]);
						cout<<YELLOW"Reading "RESET<<args[1]<<" @"<<a<<"..."<<endl;  
						result = reader(args[1], a, blockBuffer);
						break;
			case 'D':	args[1] = strtok(args[1],"\n");
						cout<<YELLOW"Deleting "RESET<<args[1]<<"..."<<endl;
						result = deleter(args[1]);
						break;
			case 'L':	cout<<YELLOW"Listing"RESET<<"..."<<endl;
						result = ls();
						break;
			case 'P':	cout<<RED"PRINTDISK..."RESET<<endl;
						rewind(fptr);
						for(i=0;i<128;i++){
							fread(blockBuffer, sizeof(char), 1024, fptr);
							cout<<i<<" ";
							for(j=0;j<50;j++){
								cout<<(int)blockBuffer[i]<<" ";
							}
							cout<<endl;
						}
						break;
			case 'Z':	cout<<RED"REFORMAT..."RESET<<endl;
						for(i=0;i<128;i++){
							freeBlockList[i]=0;
						}
						freeBlockList[0]=1;
						fseek(fptr, 128, SEEK_SET);
						for(i=0;i<16;i++){
							fread(&temp, sizeof(char), 48, fptr);
							temp.used=FREE;
							fseek(fptr, -48, SEEK_CUR);
							fwrite(&temp, sizeof(char), 48, fptr);
						}
						rewind(fptr);
						fwrite(freeBlockList, 128, sizeof(char), fptr);
						result=0;
						break;
			default:
						last = strtok(args[0]," \n\?");
						cout<<"Creating new file named \""<<last<<"\". If this was not your intention, please rewrite the input file."<<endl;
						result = FileSystem(last);
		}
		if(result==0)
			printf(GREEN"\t[SUCCESS]"RESET"\n");
		else
			printf(RED"\t[FAILURE]"RESET"\n");
		for(i=0;i<30;i++)
			buffer[i] = '0';
	}

}
