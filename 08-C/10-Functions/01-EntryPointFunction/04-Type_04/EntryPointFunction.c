#include <stdio.h>

int main(int argc, char *argv[])
{
	//variable declarations
	int ac_i;

	//code
	printf("\n");
	printf("Hello World !!!\n\n"); //Library function
	printf("Number Of Command Line Arguments = %d\n\n", argc);
	printf("Command Line Arguments Passed To This Program Are : \n\n");

	for (ac_i = 0; ac_i < argc; ac_i++)
	{
		printf("Command Line Argument %d is %s\n", (ac_i + 1), argv[ac_i]);
	}

	printf("\n");

	return (0);
}
