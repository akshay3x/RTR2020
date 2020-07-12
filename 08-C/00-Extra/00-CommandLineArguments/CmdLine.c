#include <stdio.h> 
#include <ctype.h>  // for atoi()
#include <stdlib.h> // for exit()

int main(int argc, char *argv[], char *envp[])
{
	//variable declarations
	int ac_i;
	int ac_num;
	int Result = 0;
	int SumResult = 0;
	int SubResult = 0;
	int MulResult = 1;
	int DivResult = 1;

	//code
	if(argc <= 3)
	{
		printf("\n");
		printf("More Than 2 commandline arguments provided.\n");
		printf("Exiting...\n");
		exit(0);
	}

	printf("\n");
	switch(argv[1][0])
	{
		case '+':
			SumResult = atoi(argv[2]);
			for (ac_i = 3; ac_i < argc; ac_i++)
			{
				ac_num = atoi(argv[ac_i]);
				SumResult = SumResult + ac_num;
			}
			Result = SumResult;
			break;

		case '-':
			SubResult = atoi(argv[2]);
			for (ac_i = 3; ac_i < argc; ac_i++)
			{
				ac_num = atoi(argv[ac_i]);
				SubResult = SubResult - ac_num;
			}
			Result = SubResult;
			break;
		case '*':
			MulResult = atoi(argv[2]);
			for (ac_i = 3; ac_i < argc; ac_i++)
			{
				ac_num = atoi(argv[ac_i]);
				MulResult = MulResult * ac_num;
			}
			Result = MulResult;
			break;
			
		case '/':
			printf("Division is not allowed!\n", Result);
			break;
		
		default:
			break;
	}
	printf("Result is %d\n\n", Result);

	return(0);
}
