#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	for (ac_i = 11; ac_i <= 20; ac_i++)
	{
		printf("|Outer Loop i = %d\n", ac_i);
		printf("|--------\n");

		for (ac_j = 10; ac_j <= 15; ac_j++)
		{
			printf("|\t|---Inner Loop j = %d\n", ac_j);
		}

		printf("|--------------------------\n");
	}

	return(0);
}
