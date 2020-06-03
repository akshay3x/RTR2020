#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i_num, ac_num, ac_i;

	//code
	printf("\n");
	printf("Enter An Integer Value For Iteration:");
	scanf("%d", &ac_i_num);
	
	printf("How Many Digits Do You Want To Print From %d Onwards ?:", ac_i_num);
	scanf("%d", &ac_num);

	printf("Printing Digits %d to %d : \n\n", ac_i_num, (ac_i_num + ac_num));

	for (ac_i = ac_i_num; ac_i <= (ac_i_num + ac_num); ac_i++)
	{
		printf("\t %d \n", ac_i);
	}

	printf("\n");

	return (0);
}
