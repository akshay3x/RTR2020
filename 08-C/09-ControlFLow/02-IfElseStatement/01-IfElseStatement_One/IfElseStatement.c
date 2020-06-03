#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_a, ac_b, ac_c;

	//code
	ac_a = 6;
	ac_b = 60;
	ac_c = 90;
	
	// *** FIRST if-else PAIR ***
	printf("\n");
	if (ac_a < ac_b)
	{
	printf("Entering in 1st if-block...\n");
	printf("A = %d is less than B = %d!!\n", ac_a, ac_b);
	}
	else
	{
	printf("Entering in 1st else-block...\n");
	printf("A = %d is NOT less than B = %d!\n", ac_a, ac_b);
	}

	printf("1st if-else pair done !!!\n\n");

	// *** SECOND if-else PAIR ***
	printf("\n");
	if (ac_b != ac_c)
	{
	printf("Entering in 2nd if-block...\n");
	printf("B = %d is NOT equal to C = %d!\n", ac_b, ac_c);
	}
	else
	{
	printf("Entering in 2nd else-block...\n\n");
	printf("B = %d is equal to C = %d!\n", ac_b, ac_c);
	}

	printf("2nd if-else pair done !\n");

	return(0);
}
