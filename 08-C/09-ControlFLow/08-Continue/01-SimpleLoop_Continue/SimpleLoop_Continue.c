#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i;

	//code
	printf("\n");
	printf("Printing multiples of 3 from 0 to 150:\n\n");
	for (ac_i = 0; ac_i <= 150; ac_i++)
	{
		if (ac_i % 3 != 0)
		{
			continue;
		}

		else
		{
			printf("\t %d \n", ac_i);
		}
	}

	printf("\n");

	return(0);
}
