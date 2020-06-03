#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_age;

	//code
	printf("\n");
	printf("Enter Age : ");
	scanf("%d", &ac_age);
	printf("\n");
	
	if (ac_age >= 18)
	{
	printf("Entering if-block =>\n");
	printf("You are eligible for voting!\n");
	}
	else
	{
	printf("Entering else-block =>\n");
	printf("You are NOT eligible for voting!\n");
	}

	printf("Bye Bye!!\n");

	return(0);
}
