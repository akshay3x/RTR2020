#include <stdio.h>

int main(void)
{
	//variable declarations
	char ac_option, ac_ch = '\0';

	//code
	printf("\n");
	printf("Enter Q / q to quit the infinite FOR loop :\n");
	printf("Enter Y / y to initiate the Loop:");

	ac_option = getch();

	if (ac_option == 'Y' || ac_option == 'y')
	{
		while (1) 
		{
			printf("\n");
			printf("In the loop. ");
			printf("Enter Q / q to quit:");
			ac_ch = getch();

			if (ac_ch == 'Q' || ac_ch == 'q')
			break;
			
		}

		printf("\n\n");
		printf("Exiting the loop...");
		printf("\n\n");
	}

	else
	{
		printf("\n\n");
		printf("Please Try Again.\n");
	}

	return (0);
}
