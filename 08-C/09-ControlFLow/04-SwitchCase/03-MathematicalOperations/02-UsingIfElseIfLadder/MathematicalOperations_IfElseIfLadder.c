#include <stdio.h>
#include <conio.h>

int main(void)
{

	//variable declarations
	int ac_a, ac_b;
	int ac_result;
	char ac_option, ac_option_division;

	//code
	printf("Enter a value for 'A': ");
	scanf("%d", &ac_a);
	
	printf("Enter a value for 'B': ");
	scanf("%d", &ac_b);

	printf("\n");
	printf("Enter Option In Character :\n");
	printf("'A/a' : Addition  \n");
	printf("'S/s' : Subtraction  \n");
	printf("'M/m' : Multiplication  \n");
	printf("'D/d' : Division : \n");
	
	printf("Enter Option : ");
	ac_option = getch();

	printf("\n\n");
	if (ac_option == 'A' || ac_option == 'a')
	{
	ac_result = ac_a + ac_b;
	printf("A = %d + B = %d = %d!\n", ac_a, ac_b, ac_result);
	}
	
	else if (ac_option == 'S' || ac_option == 's')
	{
		if (ac_a >= ac_b)
		{
		ac_result = ac_a - ac_b;
		printf(" B = %d - A = %d = %d!\n", ac_b, ac_a, ac_result);
		}
		else
		{
		ac_result = ac_b - ac_a;
		printf(" A = %d - B = %d = %d!\n", ac_a, ac_b, ac_result);
		}
	}
	
	else if(ac_option == 'M' || ac_option == 'm')
	{
		ac_result = ac_a * ac_b;
		printf(" A = %d * B = %d = %d!\n", ac_a, ac_b, ac_result);
	}

	else if (ac_option == 'D' || ac_option == 'd')
	{
	printf("\n");
	printf("Enter Option In Character :\n");
	printf(" Q/q  or  / For Quotient Upon Division : \n");
	printf(" R/r  or  %% For Remainder Upon Division : \n");
	printf("Enter Option : ");
	ac_option_division = getch();
	printf("\n\n");
	
	if (ac_option_division == 'Q' || ac_option_division == 'q' || ac_option_division == '/')
	{
		if (ac_a >= ac_b)
		{
			ac_result = ac_a / ac_b;
			printf(" A = %d / B = %d = %d!\n", ac_a, ac_b, ac_result);
		}
		
		else
		{
			ac_result = ac_b / ac_a;
			printf(" B = %d / A = %d = %d!\n", ac_b, ac_a, ac_result);
		}
	}

	else if (ac_option_division == 'R' || ac_option_division == 'r' || ac_option_division == '%')
	{
		if (ac_a >= ac_b)
		{
			ac_result = ac_a % ac_b;
			printf(" A = %d / B = %d Remainder = %d!\n", ac_a, ac_b, ac_result);
		}

		else
		{
			ac_result = ac_b % ac_a;
			printf(" B = %d / A = %d Remainder = %d!\n", ac_b, ac_a, ac_result);
		}

	}

	else
		printf("Invalid character %c \n", ac_option_division);
	}
else
	printf("Invalid character %c \n", ac_option);

	printf("If - Else If - Else Ladder Complete!\n");

	return(0);
}
