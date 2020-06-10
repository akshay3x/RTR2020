#include <stdio.h> 
#include <ctype.h>  // for atoi()
#include <stdlib.h> // for exit()

int main(int argc, char *argv[], char *envp[])
{
	//variable declarations
	int ac_i;
	int ac_num;
	int ac_sum = 0;

	//code
	if(argc == 1)
	{
		printf("\n\n");
		printf("No commandline arguments provided.\n\n");
		printf("Exiting...\n");

		exit(0);
	}
	
	printf("\n\n");
	printf("Sum of integers in command line arguments of");

	for (ac_i = 1; ac_i < argc; ac_i++)
	{	
		ac_num = atoi(argv[ac_i]);
		printf(" %d, ", ac_num);
		ac_sum = ac_sum + ac_num;
	}

	printf(" is %d\n\n", ac_sum);

	return(0);
}
