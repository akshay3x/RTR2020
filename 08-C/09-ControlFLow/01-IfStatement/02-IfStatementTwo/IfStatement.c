#include <stdio.h>

int main(void)
{

	//variable declarations
	int age;

	//code
	printf("Enter Age : ");
	scanf("%d", &age);

	if (age >= 18)
	{
	printf("\nYou are eligible for voting!!\n");
	}

	return(0);
}
