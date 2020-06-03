#include <stdio.h>
int main(void)
{
	//variable declarations
	char ac_option, ac_ch = '\0';

	//code
	printf("\n");
	printf("Enter Q / q to quit the loop:\n\n");

	printf("Enter Y / y to initiate loop:");
	
	ac_option = getch();
	
	if (ac_option == 'Y' || ac_option == 'y')
	{
		do
		{
			printf("\n");
			printf("In the Loop ");
			printf("Enter Q / q to quit the loop:");
			ac_ch = getch();

			if (ac_ch == 'Q' || ac_ch == 'q')
				break;

		} while (1); //Infinite Loop

		printf("\n\n");
		printf("Exiting from the loop...");
		printf("\n");
	}

	else
	{
		printf("\n\n");
		printf("Press Y / y to initiate loop. Please try again.\n");
	}

	return (0);
}
