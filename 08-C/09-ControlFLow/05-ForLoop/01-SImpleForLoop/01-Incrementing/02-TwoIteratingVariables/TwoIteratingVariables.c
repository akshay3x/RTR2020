#include <stdio.h>

int main(void)
{

	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	printf("Printing Digits 1 to 10 and 10 to 100 :\n");

	for (ac_i = 11, ac_j = 110; ac_i <= 20, ac_j <= 200; ac_i++, ac_j = ac_j + 10)
	{
		printf("\t %d \t %d\n", ac_i, ac_j);
	}

	printf("\n");

	return(0);
}
