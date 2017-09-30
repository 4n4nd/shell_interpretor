#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	char* arg[] = {"ls", "-l", NULL};
	pid_t pid = fork();
	// printf("%s\n",argv);
	printf("%s\n",execvp(*arg,arg));
	return 0;
}