#include <stdio.h>
#include <conio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	//
	for (ac_i = 1; ac_i <= 30; ac_i++)
	{
		for (ac_j = 1; ac_j <= 30; ac_j++)
		{
			if (ac_i < ac_j)
			{
				break;
			}

			else
			{
				printf("* ");
			}

		}
		printf("\n");
	}

	printf("\n");

	return (0);
}
