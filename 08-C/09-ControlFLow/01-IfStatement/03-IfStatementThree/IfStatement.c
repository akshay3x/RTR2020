#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_num;

	//code
	printf("Enter Value(A): ");
	scanf("%d", &ac_num);

	if (ac_num < 0)
	{
	printf("A = %d is Negative.\n\n", ac_num);
	}
	
	if ((ac_num > 0) && (ac_num <= 100))
	{
	printf("A = %d is between 0 and 100.\n", ac_num);
	}
	
	if ((ac_num > 100) && (ac_num <= 200))
	{
	printf("A = %d is between 100 and 200.\n", ac_num);
	}
	
	if ((ac_num > 200) && (ac_num <= 300))
	{
	printf("A = %d is between 200 and 300.\n", ac_num);
	}
	
	if ((ac_num > 300) && (ac_num <= 400))
	{
	printf("A = %d is between 300 and 400.\n", ac_num);
	}
	
	if ((ac_num > 400) && (ac_num <= 500))
	{
	printf("A = %d is between 400 and 500.\n", ac_num);
	}
	
	if (ac_num > 500)
	{
	printf("A = %d as greater than 500.\n", ac_num);
	}

	return(0);
}