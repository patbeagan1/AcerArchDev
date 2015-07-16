#include <stdio.h>

int main(){

	FILE* file;
	FILE* ofile;
	char* i;
	char oldc, newc, c='\n';
	char input[20];

	printf("NOTE: this character changer software only works on a file named \"input.txt\". Your results are in output.txt.\n");
	printf("Please rename your file if you need to.\n");

	printf("Type the character you want to replace\n");
	scanf("%c", &oldc);
	printf("Type the new character\n");
	scanf("\n%c", &newc);

//	strcpy(input, i);

	file = fopen("input.txt", "r");
	ofile = fopen("output.txt", "w");
	if (file!=NULL)
  		{
			printf("Starting work.\n");
			while(c != EOF){
				c = fgetc(file);
				if(c == oldc){
					fputc(newc, ofile);
				}
				else{
					fputc(c, ofile);
				}
			}
		}
	fclose(file);
	printf("Finished work.\n");
}
