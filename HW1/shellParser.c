#include <stdio.h>
#include <string.h>
// #include <conio.h>

int EXIT = 0;
int main(){
	int myInt = 0;
	char *name;
	// string name;
	while(!EXIT){
		printf("bash@anand~# ");
		fgets(name,100,stdin);	
		if(!strncmp("exit",name,4))
		{
			EXIT=1;
			printf("Bye!\n");
		}
	}
	
	return 0;
}