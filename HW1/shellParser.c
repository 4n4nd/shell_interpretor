#include <stdio.h>
#include <string.h>
// #include <conio.h>

int EXIT = 0;	//Main Global Variable to control the state of the state machine

int main(){
	int myInt = 0;
	char *command;
	// string command;
	while(!EXIT){
		printf("\e[91m""bash@anand~# ""\e[0m");
		fgets(command,100,stdin);	

		if(!strncmp("exit",command,4))
		{
			EXIT=1;
			printf("Bye!\n");
		}
	}
	
	return 0;
}