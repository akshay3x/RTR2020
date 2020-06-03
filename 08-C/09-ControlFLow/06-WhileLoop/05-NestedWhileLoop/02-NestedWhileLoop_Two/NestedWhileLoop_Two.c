#include <stdio.h>

int main(void)
{

	//variable declarations
	int ac_i, ac_j, ac_k;

	//code
	printf("\n");
	ac_i = 11;

	while (ac_i <= 15)
	{
		printf("|Outer while i = %d\n", ac_i);
		printf("|-------->\n");
		ac_j = 5;

		while (ac_j <= 9)
		{
			printf("|\t| Inner while j = %d\n", ac_j);
			printf("|\t|-------->\n");
			ac_k = 3;
			
			while (ac_k <= 6)
			{
				printf("|\t|\t| Innermost while k = %d\n", ac_k);
				ac_k++;
			}
			
			printf("----------------------------------\n");
			ac_j++;
		}
		printf("----------------------------------\n");
		ac_i++;
	}

	return (0);
}
