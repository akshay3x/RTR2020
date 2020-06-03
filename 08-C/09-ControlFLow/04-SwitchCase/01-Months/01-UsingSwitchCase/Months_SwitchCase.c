#include <stdio.h>

int main(void)
{
	//variable declarations
	int ac_num_month;

	//code
	
	printf("Enter a number for month (1 to 12):");
	scanf("%d", &ac_num_month);
	printf("\n");
	
	switch (ac_num_month)
	{
		case 1:
		printf("Month %d is January!\n", ac_num_month);
		break;

		case 2:
		printf("Month %d is FEBRUARY!\n", ac_num_month);
		break;

		case 3:
		printf("Month %d is MARCH!\n", ac_num_month);
		break;

		case 4:
		printf("Month %d is APRIL!\n", ac_num_month);
		break;

		case 5:
		printf("Month %d is MAY!\n", ac_num_month);
		break;

		case 6:
		printf("Month %d is JUNE!\n", ac_num_month);
		break;

		case 7:
		printf("Month %d is JULY!\n", ac_num_month);
		break;

		case 8:
		printf("Month %d is AUGUST!\n", ac_num_month);
		break;

		case 9:
		printf("Month %d is SEPTEMBER!\n", ac_num_month);
		break;

		case 10:
		printf("Month %d is OCTOBER!\n", ac_num_month);
		break;

		case 11:
		printf("Month %d is NOVEMBER!\n", ac_num_month);
		break;

		case 12:
		printf("Month %d is DECEMBER!\n", ac_num_month);
		break;

		default:
		printf("Invalid Number %d Entered!\n", ac_num_month);

		break;
	}

	printf("Switch case block complete!\n");

	return(0);
}