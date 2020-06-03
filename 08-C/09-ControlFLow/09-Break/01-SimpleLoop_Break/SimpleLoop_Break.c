#include <stdio.h>
#include <conio.h>

int main(void)
{
	//variable declarations
	int ac_i;
	char ac_ch;

	//code
	printf("\n");

	for (ac_i = 1; ac_i <= 100; ac_i++)
	{
		printf("Enter Q / q to quit. Press Any other key to continue printing:");
		printf("\t %d \n", ac_i);
		ac_ch = getch();

		if (ac_ch == 'Q' || ac_ch == 'q')
		{
			break;
		}
	}

	printf("\n");
	printf("Exiting the loop...");
	printf("\n");

	return(0);
}
