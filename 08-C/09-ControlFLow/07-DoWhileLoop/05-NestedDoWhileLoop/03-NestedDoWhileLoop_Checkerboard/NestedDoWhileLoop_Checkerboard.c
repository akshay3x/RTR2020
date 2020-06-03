#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j, ac_c;

	//code
	printf("\n\n");
	ac_i = 0;
	do
	{
		ac_j = 0;
		
		do
		{
			ac_c = ((ac_i & 0x8) == 0) ^ ((ac_j & 0x8) == 0);

			if (ac_c == 0)
				printf("  ");
			
			if (ac_c == 1)
				printf("* ");
			
			ac_j++;
		} while (ac_j < 64);

		printf("\n");
		ac_i++;

	} while (ac_i < 64);

	return(0);
}
