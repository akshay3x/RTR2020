#include <stdio.h>
//m#include <stdlib.h>
int main(void)
{
	//variable declarations
	char ac_option, ac_ch = '\0';

	//code
	printf("\n");
	//printf("Enter Q / q to exit from the loop:\n");

	do
	{
		do
		{
			printf("\n");
			printf("In the loop.  ");
			printf("Enter Q / q to exit from the loop:");
			ac_ch = getch(); 

		} while (ac_ch != 'Q' && ac_ch != 'q');

		printf("\n");
		printf("Exiting the Loop...");
		printf("\n");
		printf("To Begin again enter Y / y:");

		ac_option = getch();
		
	} while (ac_option == 'Y' || ac_option == 'y');

	printf("\nExiting...");

	return(0);
}
