#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j, ac_c;

	//code
	printf("\n");
	for (ac_i = 0; ac_i < 64; ac_i++)
	{
		for (ac_j = 0; ac_j < 64; ac_j++)
		{
			ac_c = ((ac_i & 0x8) == 0) ^ ((ac_j & 0x8) == 0);

			if (ac_c == 0)
			printf("  ");

			if (ac_c == 1)
			printf("* ");
		}

		printf("\n");
	}

	return(0);
}
