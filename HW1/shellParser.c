#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
// #include <conio.h>

int EXIT = 0;	//Main Global Variable to control the state of the state machine

int executeProcess(int ampersAnd,char* newCommandArg[]){
	int pid = fork();
	int status;
	if (pid==0)
	{
		printf("%d\n",execvp(newCommandArg[0], newCommandArg));

	}else
	{

		if (!ampersAnd)
		{
			while (wait(&status) != pid);
		}else{
			printf("%d\n",pid);
		}
			// printf("I am the Parent with pid:%d \n", pid);
			

	}
	return pid;
}
int tokenizer(char command[], char * newCommandArg[]){
	char commandList[100][500]={{'\0'}}; // Command List to tokenize commands including white spaces



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

		// *tokenArray = (char **)malloc(150);

		for (int i = 0; i < commandState+1; ++i)			//loop to remove empty items
		{
			if (strncmp(commandList[i],"",1)!=0)
			{

				// strcpy(tokenArray[tokenIter],strcat(commandList[i],"\0"));
				newCommandArg[tokenIter]=commandList[i];
				tokenIter++;


			} 
		}
		return tokenIter;
}

int main(){
	int myInt = 0;

	// string command;
	
	while(!EXIT){
		// char command[100];
		char command[1000];// = &comArray; //Buffer Array to store user input stream
		// printf("\e[36m""bash@anand~# ""\e[0m"); //User Bash input custom
		printf("my_shell>");		//User Bash input traditional
		fgets(command,1000,stdin); //Take user input and sore it to command buffer
		char* newCommandArg[100]={NULL};//=tokenArray; 
		int tokenIter = tokenizer(command,newCommandArg);

		// char commandList[100][500]={{'\0'}}; // Command List to tokenize commands including white spaces



		// // const char delim1 = ' ';
		// // const char delim2 = '	';
		
		// // printf("Command -> %s\n",strsep(&command,&delim1));
		// int commandState = 0;		//iterator to change to next token
		// // int piper=0;
		// int stringIter = 0;	// iterator for next character
		// for (int i = 0; i < strlen(command)-1; ++i)
		// {
		// 	if (command[i]!=' ' && command[i]!='&' && command[i]!='|' && command[i]!='	'&& command[i]!='>' && command[i]!='<')	// excluding meta characters
		// 	{
		// 		commandList[commandState][stringIter]=command[i];
		// 		stringIter++;

		// 		// printf("Break Here.\n");
		// 		// printf("%c\n", command[i]);

		// 	}else
		// 	{	
		// 		// printf("%i\n", i);
		// 		stringIter++;
		// 		commandList[commandState][stringIter]='\0';
		// 		stringIter=0;

		// 		commandState++;
		// 		if (command[i]=='&'||command[i]=='|'||command[i]=='>'||command[i]=='<')	//excluding white spaces
		// 		{
		// 			// commandState++;
		// 			commandList[commandState][stringIter]=command[i];
		// 			commandState++;

		// 		}
				
		// 		// printf("Break Here.\n");

		// 	}
		// }
		// int tokenIter=0;

		// char tokenArray[100][100];//={{NULL}};
		// char* newCommandArg[100]={NULL};//=tokenArray; 

		// // *tokenArray = (char **)malloc(150);

		// for (int i = 0; i < commandState+1; ++i)			//loop to remove empty items
		// {
		// 	if (strncmp(commandList[i],"",1)!=0)
		// 	{

		// 		strcpy(tokenArray[tokenIter],strcat(commandList[i],"\0"));
		// 		newCommandArg[tokenIter]=commandList[i];
		// 		tokenIter++;


		// 	} 
		// }

		
		// strcpy(tokenArray[tokenIter+1],"");	//Added a null to the end of string array
		// printf("%s let's see 2\n",tokenArray);

		// {
		// }

		int state =0;
		char printedString[20] = "Command";
		int pipeIndexArray[100];
		int pipeArrayIter = 0;
		int ampersAnd = 0;
		for (int i = 0; i < tokenIter; ++i)			// state machine to categorize all tokens for output
		{	
			if (state==1)
			{
				strcpy(printedString,"Argument");
			}else{
				strcpy(printedString,"Command");
				state=1;
			}
			if (strcmp(newCommandArg[i],"|")==0)
			{
				strcpy(printedString,"Pipe");
				state=0;
				pipeIndexArray[pipeArrayIter]=i;
				pipeArrayIter++;
			}
			if (strcmp(newCommandArg[i],">")==0)
			{
				strcpy(printedString,"Output redirect");
				
			}
			if (strcmp(newCommandArg[i],"<")==0)
			{
				strcpy(printedString,"Input redirect");
				
			}
			if (strcmp(newCommandArg[i],"&")==0)
			{
				strcpy(printedString,"Background");
				newCommandArg[i]="";
				ampersAnd=1;
				
			}
			// printf("%s - %s\n",tokenArray[i],printedString );
			if (strcmp(newCommandArg[i],"exit")==0)
			{
				EXIT=1;
				exit(0);
			}
		}

		// printf("I found pipes at");

		char* pipedArg[100];
		for (int i = 0; i < pipeArrayIter; ++i)
		{
			
		}
		executeProcess(ampersAnd,newCommandArg);
		
		
		
	}
	
	return 0;
}