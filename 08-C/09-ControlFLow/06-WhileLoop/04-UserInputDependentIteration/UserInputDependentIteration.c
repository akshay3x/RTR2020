#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_i_num, ac_num, ac_i;

	//code
	printf("aaaa\n");
	printf("Enter integer from to iteration begin:");
	scanf("%d", &ac_i_num);

	printf("Number of digits do you want to print from %d onwards:", ac_i_num);
	scanf("%d", &ac_num);

	printf("Printing %d to %d:\n\n", ac_i_num, (ac_i_num + ac_num));
	ac_i = ac_i_num;

	while (ac_i <= (ac_i_num + ac_num))
	{
		printf("\t %d \n", ac_i);
		ac_i++;
	}

	printf("\n");

	return(0);
}
