#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_a;

	//code
	printf("\n\n");
	ac_a = 10;

	if (ac_a)
	{
	printf("Non-zero Positive Value = %d!\n", ac_a);
	}

	ac_a = -10;
	if (ac_a)
	{
	printf("Non-zero Negative Value = %d!\n", ac_a);
	}

	ac_a = 0;
	if (!ac_a) // 
	{
	printf("Zero Value = %d!\n\n", ac_a);
	}

	printf("All three if-statements are done!\n\n");

	return(0);
}
