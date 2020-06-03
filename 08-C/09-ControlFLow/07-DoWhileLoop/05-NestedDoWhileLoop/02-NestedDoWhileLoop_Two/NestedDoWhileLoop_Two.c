#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j, ac_k;

	//code
	printf("\n");

	ac_i = 1;
	printf("----------------------------------\n");
	do
	{
		printf("|Outer loop i = %d\n", ac_i);
		printf("|--------------------------------\n");
		
		ac_j = 1;
		
		do
		{
			printf("|\t|Inner loop j = %d\n", ac_j);
			printf("|\t|-------\n");
			
			ac_k = 1;

			do
			{
				printf("|\t|\t| Innermost k = %d\n", ac_k);
				ac_k++;
			} while (ac_k <= 2);

			//printf("\n");
			ac_j++;

		} while (ac_j <= 3);

		printf("---------------------------------\n");
		ac_i++;

	} while (ac_i <= 8);

	return(0);
}
