#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_num;

	//code
	printf("Enter Value For A : ");
	scanf("%d", &ac_num);
	
	printf("\n");
	if (ac_num < 0) // 'if' - 01
	{
	printf("A = %d is Negative!\n", ac_num);
	}
	else // 'else' - 01
	{
		if ((ac_num > 0) && (ac_num <= 100)) // 'if' - 02
		{
		printf("A = %d is between 0 and 100!\n", ac_num);
		}
		else // 'else' - 02
		{
			if ((ac_num > 100) && (ac_num <= 200)) // 'if' - 03
			{
			printf("A = %d is between 100 and 200!\n", ac_num);
			}
			else // 'else' - 03
			{
				if ((ac_num > 200) && (ac_num <= 300)) // 'if' - 04
				{
				printf("A = %d is between 200 and 300!\n", ac_num);
				}
				else // 'else' - 04
				{
					if ((ac_num > 300) && (ac_num <= 400)) // 'if' - 05
					{
					printf("A = %d is between 300 and 400!\n", ac_num);
					}
					else // 'else' - 05
					{
						if ((ac_num > 400) && (ac_num <= 500)) // 'if' - 06
						{
						printf("A = %d is between 400 and 500!\n", ac_num);
						}
						else // 'else' - 06
						{
						printf("A = %d is greater than 500!\n", ac_num);
						} // closing 'else' - 06
						
					}// closing 'else' - 05
					
				}// closing 'else' - 04
				
			}// closing 'else' - 03
		}// closing 'else' - 02
		
	}// closing 'else' - 01
	
	return (0);
}
