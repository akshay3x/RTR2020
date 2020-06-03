#include<stdio.h>

int main(void)
{
	//variable declarations
	int i, j, k;

	//code
	printf("\n");

	for (i = 11; i <= 20; i++)
	{
		printf("|Outer i = %d\n", i);
		printf("|--------\n");
		
		for (j = 1; j <= 3; j++)
		{
			printf("|\t| Inner j = %d\n", j);
			printf("|\t|--------\n");

			for (k = 1; k <= 6; k++)
			{
				printf("|\t|\t|Innermost k = %d\n", k);
			}

		printf("|\t|----------------------\n");
		}
	
	printf("|------------------------------\n");
	}

	return(0);
}
