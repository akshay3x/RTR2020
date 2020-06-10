#include <stdio.h>

int main(int argc, char *argv[], char *envp[])
{
	//variable declarations
	int i;

	//code
	printf("\n");
	printf("Hello World!\n\n"); //Library function
	printf("Number Of Command Line Arguments = %d\n", argc);
	printf("Command Line Arguments Passed To This Program Are : \n\n");

	for (i = 0; i < argc; i++)
	{
		printf("Command Line Argument Number %d = %s\n", (i + 1), argv[i]);
	}

	printf("\n\n");
	printf("First 20 Environmental Variables Passed To This Program Are :\n");

	for (i = 0; i < 20; i++)
	{
		printf("Environmental Variable %d. = %s \n", (i + 1), envp[i]);
	}

	printf("\n\n");

	return (0);
}
