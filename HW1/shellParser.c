#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
// #include <conio.h>

int EXIT = 0;	//Main Global Variable to control the state of the state machine


// void  execute(char **argv)
// {
//      pid_t  pid;
//      int    status;

//      if ((pid = fork()) < 0) {     /* fork a child process           */
//           printf("*** ERROR: forking child process failed\n");
//           exit(1);
//      }
//      else if (pid == 0) {          /* for the child process:         */
//           if (execvp(*argv, argv) < 0) {     /* execute the command  */
//                printf("*** ERROR: exec failed\n");
//                exit(1);
//           }
//      }
//      else {                                  /* for the parent:      */
//           while (wait(&status) != pid)       /* wait for completion  */
//                ;
//      }
// }
int main(){
	int myInt = 0;

	// string command;
	
	while(!EXIT){
		// char command[100];
		char command[1000];// = &comArray; //Buffer Array to store user input stream
		char commandList[100][500]={{'\0'}}; // Command List to tokenize commands including white spaces

		printf("\e[36m""bash@anand~# ""\e[0m"); //User Bash input custom
		// printf("myParser>");		//User Bash input traditional
		fgets(command,1000,stdin); //Take user input and sore it to command buffer

		// const char delim1 = ' ';
		// const char delim2 = '	';
		
		// printf("Command -> %s\n",strsep(&command,&delim1));
		int commandState = 0;		//iterator to change to next token
		// int piper=0;
		int stringIter = 0;	// iterator for next character
		for (int i = 0; i < strlen(command)-1; ++i)
		{
			if (command[i]!=' ' && command[i]!='&' && command[i]!='|' && command[i]!='	'&& command[i]!='>' && command[i]!='<')	// excluding meta characters
			{
				commandList[commandState][stringIter]=command[i];
				stringIter++;

				// printf("Break Here.\n");
				// printf("%c\n", command[i]);

			}else
			{	
				// printf("%i\n", i);
				stringIter++;
				commandList[commandState][stringIter]='\0';
				stringIter=0;

				commandState++;
				if (command[i]=='&'||command[i]=='|'||command[i]=='>'||command[i]=='<')	//excluding white spaces
				{
					// commandState++;
					commandList[commandState][stringIter]=command[i];
					commandState++;

				}
				
				// printf("Break Here.\n");

			}
		}
		int tokenIter=0;

		char tokenArray[100][100];//={{NULL}};
		char* newCommandArg[100];//=tokenArray; 

		// *tokenArray = (char **)malloc(150);

		for (int i = 0; i < commandState+1; ++i)			//loop to remove empty items
		{
			// printf("%i\n",strncmp(commandList[i],"",1));
			if (strncmp(commandList[i],"",1)!=0)
			{
				// printf("%s\n",commandList[i]);
						// printf("This is murica\n");

				strcpy(tokenArray[tokenIter],strcat(commandList[i],"\0"));
				newCommandArg[tokenIter]=commandList[i];
				tokenIter++;
						// printf("This is murica\n");

				// *tokenArray++;


			} 
			// printf("%s\n",commandList[i]);
			// ++tokenArray[tokenIter]="\0";
		}

		// for (int i = 0; i < tokenIter; ++i)
		// {
			// newCommandArg[i]=tokenArray[i];
		// }
		// char *nullStr = NULL;
		// printf("%s let's see\n",tokenArray);
		// tokenIter++;
		// printf("%d\n",tokenIter );
	/*	strcpy(tokenArray[tokenIter+1],"");	//Added a null to the end of string array
		// printf("%s let's see 2\n",tokenArray);

		// {
		// }
		int state =0;
		char printedString[20] = "Command";
		for (int i = 0; i < tokenIter; ++i)			// state machine to categorize all tokens for output
		{	
			if (state==1)
			{
				strcpy(printedString,"Argument");
			}else{
				strcpy(printedString,"Command");
				state=1;
			}
			if (strcmp(tokenArray[i],"|")==0)
			{
				strcpy(printedString,"Pipe");
				state=0;
			}
			if (strcmp(tokenArray[i],">")==0)
			{
				strcpy(printedString,"Output redirect");
				
			}
			if (strcmp(tokenArray[i],"<")==0)
			{
				strcpy(printedString,"Input redirect");
				
			}
			if (strcmp(tokenArray[i],"&")==0)
			{
				strcpy(printedString,"Background");
				
			}
			printf("%s - %s\n",tokenArray[i],printedString );
			if (strcmp(tokenArray[i],"exit")==0)
			{
				EXIT=1;
			}
		}*/
		
		int pid = fork();
		int status;
		if (pid==0)
		{
			// sleep(5);
			printf("I am the child\n");
			// printf("%s\n",tokenArray );
			// system(tokenArray);
			// char* arg[] = {"ls", "-l", NULL};
			// // if (strcmp(tokenArray[2],arg[2]))
			// {
			// 	printf("It is equal\n");
			// }
			printf("%d\n",execvp(newCommandArg[0], newCommandArg));
			// execute(tokenArray);

		}else{
			// printf("jahsb hc b juvuuh\n" );
			while (wait(&status) != pid);
			// wait(1);
			printf("I am the Parent with pid:%d \n", pid);
			

		}
		// printf("%d\n",pid);
		// printf("%s\n",tokenArray[0] );

		// printf("The arraySize is: %d\n",stringLength);
		// if (command!=NULL)
		// {
		// 	printf("Attributes -> %s\n",command);
			// if(!strncmp("exit",command,4))
		// 	{
		// 		EXIT=1;
		// 		printf("Bye!\n");
		// 	}
		// }
		
	}
	
	return 0;
}