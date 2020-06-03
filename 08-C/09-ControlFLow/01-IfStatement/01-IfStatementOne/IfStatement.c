#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_a, ac_b, ac_c;
	
	//code
	ac_a = 6;
	ac_b = 53;
	ac_c = 78;
	
	printf("\n");
	if (ac_a < ac_b)
	{
	printf("A = %d is less than B = %d!\n\n", ac_a, ac_b);
	}
	if (ac_b != ac_c)
	{
	printf("B = %d is NOT equal to C = %d !\n\n", ac_b, ac_c);
	}
	printf("Both comparisons have been done !\n");
	
	return(0);
}
