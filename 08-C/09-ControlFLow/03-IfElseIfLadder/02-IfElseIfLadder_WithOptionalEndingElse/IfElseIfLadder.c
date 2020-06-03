#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_num;

	//code

	printf("Enter Value For A : ");
	scanf("%d", &ac_num);
	printf("\n");

	if (ac_num < 0)
	printf("A = %d is Negative!\n", ac_num);
	
	else if ((ac_num > 0) && (ac_num <= 100))
	printf("A = %d Is Between 0 And 100!\n", ac_num);

	else if ((ac_num > 100) && (ac_num <= 200))
	printf("A = %d Is Between 100 And 200!\n", ac_num);

	else if ((ac_num > 200) && (ac_num <= 300))
	printf("A = %d Is Between 200 And 300!\n", ac_num);

	else if ((ac_num > 300) && (ac_num <= 400))
	printf("A = %d Is Between 300 And 400!\n", ac_num);

	else if ((ac_num > 400) && (ac_num <= 500))
	printf("A = %d Is Between 400 And 500!\n", ac_num);
	
	else if (ac_num > 500)
	printf("A = %d is greater than 500!\n", ac_num);
	
	else
	printf("Invalid value entered !!!\n\n");
	
	return(0);
}