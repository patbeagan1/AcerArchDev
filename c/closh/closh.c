// closh.c - CS 377, Fall 2012
// Patrick Beagan

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#define TRUE 1
#define FALSE 0


void handler(int sig)
{
	printf("handling...");
	kill(getpid(), SIGKILL);
	printf("process %i was killed\n", getpid());
}

// tokenize the command string into arguments - do not modify
void readCmdTokens(char* cmd, char** cmdTokens) {
    cmd[strlen(cmd) - 1] = '\0'; // drop trailing newline
    int i = 0;
    cmdTokens[i] = strtok(cmd, " "); // tokenize on spaces
    while (cmdTokens[i++] && i < sizeof(cmdTokens)) {
        cmdTokens[i] = strtok(NULL, " ");
    }
}

// read one character of input, then discard up to the newline - do not modify
char readChar() {
    char c = getchar();
    while (getchar() != '\n');
    return c;
}

// main method - program entry point
int main() {
    char cmd[81]; // array of chars (a string)
    char* cmdTokens[20]; // array of strings
    int count; // number of times to execute command
    int parallel; // whether to run in parallel or sequentially
    int timeout; // max seconds to run set of commands (parallel) or each command (sequentially)
    int status;

    while (TRUE) { // main shell input loop
        
        // begin parsing code - do not modify
        printf("closh> ");
        fgets(cmd, sizeof(cmd), stdin);
        if (cmd[0] == '\n') continue;
        readCmdTokens(cmd, cmdTokens);
        do {
            printf("  count> ");
            count = readChar() - '0';
        } while (count <= 0 || count > 9);
        
        printf("  [p]arallel or [s]equential> ");
        parallel = (readChar() == 'p') ? TRUE : FALSE;
        do {
            printf("  timeout> ");
            timeout = readChar() - '0';
        } while (timeout < 0 || timeout > 9);
        // end parsing code
        
        
        ////////////////////////////////////////////////////////
        //                                                    //
        // TODO: use cmdTokens, count, parallel, and timeout  //
        // to implement the rest of closh                     //
        //                                                    //
        // /////////////////////////////////////////////////////

	signal(SIGALRM, handler);
	int i, parent;
	for(i=0; i<count; i++)
	{
		parent = fork();//fork once for each new process - gives us as many processes as count
		printf("process %i\n", getpid());

//		time_t start, end;
//		time(&start);

		if(parent)//parent is actually the pid of the child, but since it is positive this is the parent
		{
			printf("hello%i\n",parent);
//			if(timeout!=0)			//I tried to use time.h for the timer, leaving in for documentation
//				alarm(timeout);
			/*if(timeout!=0)
			{
				int y=1;
				while(y)
				{
					time(&end);

					if(difftime(end, start) > timeout)
					{
						kill(parent, SIGKILL);
						printf("process %i was killed\n", parent);
						y=0;
					}
				}
			}*/
			if(!parallel)
			{
				wait(NULL);//when sequential, wait for each process to finish before moving on to the next process
			}
			printf("goodbye%i\n", parent);

		}
		else
		{	if(timeout!=0)
			alarm(timeout);//sets an alarm at the beginning of the program which will call the handler 
					//when the program has elapsed timeout seconds
			execvp(cmdTokens[0], cmdTokens); // replaces the current process with the given program
			// doesn't return unless the calling failed
		        printf("Can't execute %s\n", cmdTokens[0]); // only reached if running the program failed
	      		exit(1);
		}
	}

	for(i=0; i<count; i++)
	wait(NULL);//at the end, wait for every process except the closh process to finish
			//keeps the prompt from displaying prematurely

}//end while
}//end main

