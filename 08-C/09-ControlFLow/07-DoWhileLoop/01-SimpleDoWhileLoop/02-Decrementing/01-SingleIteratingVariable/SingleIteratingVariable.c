#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i;

	//code
	printf("\n");
	printf("Printing Digits 9 to 0 : \n\n");

	ac_i = 9;
	
	do
	{
		printf("\t%d\n", ac_i);
		ac_i--;
	}while (ac_i >= 0);

	printf("\n");

	return(0);
}
