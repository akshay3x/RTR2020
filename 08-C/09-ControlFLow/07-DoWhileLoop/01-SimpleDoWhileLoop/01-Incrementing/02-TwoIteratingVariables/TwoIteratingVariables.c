#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	printf("Printing 11 to 20 and 110 to 200:\n\n");

	ac_i = 11;
	ac_j = 110;

	do
	{

		printf("\t %d \t %d\n", ac_i, ac_j);
		ac_i++;
		ac_j = ac_j + 10;

	} while (ac_i <= 20, ac_j <= 200);

	printf("\n");

	return (0);
}
