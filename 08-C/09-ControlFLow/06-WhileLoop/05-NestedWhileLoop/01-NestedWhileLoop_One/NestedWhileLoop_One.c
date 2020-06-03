#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	
	ac_i = 11;
	printf("|--------------------------\n");
	
	while(ac_i <= 20)
	{
		printf("|Outer loop i = %d\n", ac_i);
		printf("|--------\n");
		
		ac_j = 5;

		while (ac_j <= 10)
		{
			printf("|\t| Inner loop j = %d \n", ac_j);
			ac_j++;
		}
	
	ac_i++;
	printf("|--------------------------\n");
	}

	return (0);
}
