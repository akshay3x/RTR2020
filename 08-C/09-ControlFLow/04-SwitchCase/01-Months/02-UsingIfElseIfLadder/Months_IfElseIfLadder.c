#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_num_month;

	//code
	printf("Enter a number for month (1 to 12):");
	scanf("%d", &ac_num_month);
	printf("\n");

	if (ac_num_month == 1)
	printf("Month %d is JANUARY!\n", ac_num_month);

	else if (ac_num_month == 2)
	printf("Month %d is FEBRUARY!\n", ac_num_month);

	else if (ac_num_month == 3)
	printf("Month %d is MARCH!\n", ac_num_month);

	else if (ac_num_month == 4)
	printf("Month %d is APRIL!\n", ac_num_month);
	
	else if (ac_num_month == 5)
	printf("Month %d is MAY!\n", ac_num_month);

	else if (ac_num_month == 6)
	printf("Month %d is JUNE!\n", ac_num_month);

	else if (ac_num_month == 7)
	printf("Month %d is JULY!\n", ac_num_month);

	else if (ac_num_month == 8)
	printf("Month %d is AUGUST!\n", ac_num_month);
	
	else if (ac_num_month == 9)
	printf("Month %d is SEPTEMBER!\n", ac_num_month);
	
	else if (ac_num_month == 10)
	printf("Month %d is OCTOBER!\n", ac_num_month);

	else if (ac_num_month == 11)
	printf("Month %d is NOVEMBER!\n", ac_num_month);

	else if (ac_num_month == 12)
	printf("Month %d is DECEMBER!\n", ac_num_month);

	else 
	printf("Invalid month number %d!\n", ac_num_month);

	printf("If Else If Else Ladder Complete!\n");

	return(0);
}
