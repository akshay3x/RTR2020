#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i_num, ac_num, ac_i;

	//code
	printf("\n");
	printf("Enter integer for iteration:");
	scanf("%d", &ac_i_num);

	printf("Number of digits to print from %d onwards:", ac_i_num);
	scanf("%d", &ac_num);

	printf("Printing Digits %d to %d : \n\n", ac_i_num, (ac_i_num + ac_num));
	ac_i = ac_i_num;

	do
	{
		printf("\t %d \n", ac_i);
		ac_i++;
	} while (ac_i <= (ac_i_num + ac_num));

	printf("\n");

	return(0);
}
