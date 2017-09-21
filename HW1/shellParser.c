#include <stdio.h>
#include <string.h>
// #include <conio.h>

int EXIT = 0;	//Main Global Variable to control the state of the state machine

int main(){
	int myInt = 0;

	// string command;
	
	while(!EXIT){
		// char command[100];
		char command[1000];// = &comArray;
		char commandList[100][500]={{'\0'}};

		printf("\e[36m""bash@anand~# ""\e[0m"); 
		fgets(command,1000,stdin);
		int stringLength = strlen(command)-1;

		// const char delim1 = ' ';
		// const char delim2 = '	';
		
		// printf("Command -> %s\n",strsep(&command,&delim1));
		int commandState = 0;
		int piper=0;
		int stringIter = 0;
		for (int i = 0; i < strlen(command)-1; ++i)
		{
			if (command[i]!=' ' && command[i]!='&' && command[i]!='|' && command[i]!='	'&& command[i]!='>' && command[i]!='<')
			{
				commandList[commandState][stringIter]=command[i];
				stringIter++;
				// printf("Break Here.\n");
				// printf("%c\n", command[i]);

			}else
			{	
				// printf("%i\n", i);
				stringIter=0;
				commandState++;
				if (command[i]=='&'||command[i]=='|'||command[i]=='>'||command[i]=='<')
				{
					// commandState++;
					commandList[commandState][stringIter]=command[i];
					commandState++;

				}
				
				// printf("Break Here.\n");

			}
		}
		int tokenIter=0;
		char tokenArray[100][100]={{'\0'}};
		for (int i = 0; i < commandState+1; ++i)
		{
			// printf("%i\n",strncmp(commandList[i],"",1));
			if (strncmp(commandList[i],"",1)!=0)
			{
				// printf("%s\n",commandList[i]);
				strcpy(tokenArray[tokenIter],commandList[i]);
				tokenIter++;
			} 
		}
		int state =0;
		char printedString[20] = "Command";
		for (int i = 0; i < tokenIter; ++i)
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
		}

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