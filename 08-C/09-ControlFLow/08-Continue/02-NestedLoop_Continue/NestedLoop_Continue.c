#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	printf("Outer Loop: Multiples of 3 from 1 and 15. \n\n");
	printf("Inner Loop: Non multiples of 3 Numbers Between 1 and 15\n\n");

	printf("---------------------------\n");
	for (ac_i = 1; ac_i <= 15; ac_i++)
	{
		if (ac_i % 3 == 0) 
		{
			printf("|Outer Loop  i = %d\n", ac_i);
			printf("|--------\n");

			for (ac_j = 1; ac_j <= 15; ac_j++)
			{
				if (ac_j % 3 != 0) 
				{
					printf("|\t| Inner Loop  j = %d \n",ac_j);
				}

				else
				{
					continue;
				}
			}

			printf("|---------------------------\n");
		}

		else
		{
			continue;
		}
	}

	printf("\n");

	return (0);
}
