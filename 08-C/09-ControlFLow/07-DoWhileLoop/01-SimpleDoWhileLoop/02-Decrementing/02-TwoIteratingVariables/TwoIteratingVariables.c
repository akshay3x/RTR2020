#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	printf("Printing 10 to 1 and 100 to 10:\n\n");

	ac_i = 20;
	ac_j = 200;

	do
	{
		printf("\t %d \t %d \n", ac_i, ac_j);
		ac_i--;
		ac_j = ac_j - 10;
		
	} while (ac_i >= 11, ac_j >= 110);

	printf("\n");

	return (0);
}
