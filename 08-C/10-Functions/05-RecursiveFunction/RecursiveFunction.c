#include <stdio.h>

int main(void)
{

	// variable declarations
	unsigned int ac_num;

	// function prototype
	void ac_recursive(unsigned int);

	// code
	printf("\n");
	printf("Enter A Number :");
	scanf("%u", &ac_num);

	printf("\n");
	printf("Output Of Recursive Function :\n");

	ac_recursive(ac_num);

	printf("\n");
	
	return(0);
}

void ac_recursive(unsigned int ac_n)
{
	// code
	printf("n = %d \n", ac_n);

	if(ac_n > 0)
	{
	ac_recursive(ac_n - 1);
	}
}
