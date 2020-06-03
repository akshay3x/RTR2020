#include <stdio.h>

int main(void)
{
	//variable declarations
	char ac_option, ac_ch = '\0';

	//code
	printf("\n");
	printf("Enter Q / q to quit the loop :\n\n");
	printf("Enter Y / y to initiate loop :");


	ac_option = getch();

	if (ac_option == 'Y' || ac_option == 'y')
	{
		for (  ;  ;  )
		{
		printf("In the Loop\n");
		printf("Enter Q / q to quit the loop :");
		ac_ch = getch();

		if (ac_ch == 'Q' || ac_ch == 'q')
		break; 
		}
	}

	printf("\n\n");
	printf("Exited from the Loop\n");

	return(0);
}
