#include<stdio.h>
#include<conio.h>

int main()
{
	int ac_a, ac_b;
	int ac_result;

	char ac_option, ac_option_division;
	
	//code
	printf("\n");
	
	printf("Enter Value for A:");
	scanf("%d", &ac_a);
	
	printf("Enter Value for B:");
	scanf("%d", &ac_b);

	printf("Enter Option in character:\n");
	printf("A/a: Addtion \n");
	printf("S/s: Subtraction \n");
	printf("M/m: Multiplication \n");
	printf("D/d: Division \n");
	
	printf("Enter option: ");
	ac_option= getch();
	
	printf("\n");
	
	switch(ac_option)
	{

	case 'A':
	case 'a':
	ac_result= ac_a + ac_b;
	printf("\n");
	printf("Sum %d + %d = %d\n", ac_a, ac_b, ac_result);
	break;
	
	case 'S':
	case 's':
	if(ac_a >= ac_b)
	{
		ac_result= ac_a - ac_b;
		printf("\n");
		printf("Sum %d - %d = %d\n", ac_a, ac_b, ac_result);
	}
	else
	{
		ac_result= ac_b - ac_a;
		printf("\n");
		printf("Sum %d - %d = %d\n", ac_b, ac_a, ac_result);
	}
	break;
	
	case 'M':
	case 'm':
	ac_result= ac_a * ac_b;
	printf("\n");
	printf("Product %d * %d = %d\n", ac_a, ac_b, ac_result);
	break;
	
	case 'D':
	case 'd':
	printf("Enter an option in character\n");
	printf(" Q/q  or '/' for quotient upon division : \n");
	printf(" R/r  or '%%' for remainder upon division : \n");
	printf("Enter Option : ");

	ac_option_division = getch();
	printf("\n\n");
	
	switch (ac_option_division)
	{
		case 'Q':
		case 'q':
		case '/':
		if (ac_a >= ac_b)
		{
			ac_result = ac_a / ac_b;
			printf("\n");
			printf("A = %d / B = %d = %d!\n ", ac_a, ac_b, ac_result);
		}
		else
		{
			ac_result = ac_b / ac_a;
			printf("\n");
			printf(" B = %d / A = %d = %d!\n", ac_b, ac_a, ac_result);
		}
		break; 

		case 'R':
		case 'r':
		case '%':
		if (ac_a >= ac_b)
		{
			ac_result = ac_a % ac_b;
			printf("\n");
			printf(" A = %d / B = %d Remainder = %d!\n", ac_a, ac_b, ac_result);
		}
		
		else
		{
			ac_result = ac_b % ac_a;
			printf("\n");
			printf(" B = %d / A = %d Remainder = %d!\n", ac_b, ac_a, ac_result);
		}
		break;

		default:
		printf("\n");
		printf("Invalid Character %c Entered!\n", ac_option_division);
		break;
	}
	break;
	
	default:
	printf("\n");
	printf("Invalid Character %c Entered!\n", ac_option);
	break;
	}
	
	printf("Switch Case Block Complete!\n");

	return(0);
}
