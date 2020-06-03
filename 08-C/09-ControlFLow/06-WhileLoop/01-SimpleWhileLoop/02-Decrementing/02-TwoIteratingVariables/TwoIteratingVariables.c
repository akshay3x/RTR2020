#include <stdio.h>

int main(void)
{

	//variable declarations
	int ac_i, ac_j;

	//code
	printf("\n");
	printf("Printing 20 to 11 and 200 to 110:\n");
	
	ac_i = 20;
	ac_j = 200;

	while (ac_i >= 11, ac_j >= 110)
	{
		printf("\t %d \t %d\n", ac_i, ac_j);
		ac_i--;
		ac_j = ac_j - 10;
	}

	printf("\n");

	return(0);
}
