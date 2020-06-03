#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i;

	//code
	printf("\n");
	printf("Printing Digits 25 to 15 : \n\n");

	ac_i = 25;

	while (ac_i >= 15)
	{
	printf("\t%d\n", ac_i);
	ac_i--;
	}

	printf("\n");

	return(0);
}
