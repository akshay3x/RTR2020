#include <stdio.h> 		//for printf()
#include <stdlib.h> 	//for exit()

int main(int argc, char *argv[], char *envp[])
{
	//variable declarations
	int ac_i;

	//code
	if(argc != 4) // Program name + first name + middle name + surname = 4 command line arguments are required
	{
		printf("\n\n");
		printf("Program requires 3 command line string arguments\n");
		printf("Exiting...\n");
		
		exit(0);
	}

	printf("\n\n");
	printf("Your full name is: ");
	
	for (ac_i = 1; ac_i < argc; ac_i++)
	{
		printf("%s ", argv[ac_i]);
	}

	printf("\n\n");

	return(0);
}
