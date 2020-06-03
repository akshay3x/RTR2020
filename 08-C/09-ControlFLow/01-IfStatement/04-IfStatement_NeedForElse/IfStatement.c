#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_age;

	//code
	printf("Enter Age : ");
	scanf("%d", &ac_age);

	if (ac_age >= 18)
	{
	printf("You are eligible for voting!\n");
	}
	
	printf("You are NOT eligible for voting !\n");

	return(0);
}
