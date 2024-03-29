#include <stdio.h>

int main(void)
{
	//function prototypes
	int printBinaryFormOfNumber(unsigned int);
	
	//variable declarations
	unsigned int ac_a;
	unsigned int ac_b;
	unsigned int ac_result;

	//code
	//printf("\n");
	printf("Enter 1st integer (A) = ");
	scanf("%u", &ac_a);
	
	printf("\n");
	printf("Enter 2nd integer(B) = ");
	scanf("%u", &ac_b);
	
	printf("\n");
	
	ac_result = ac_a | ac_b;
	printf("Bitwise ORing Of \nA = (Decimal) %d  and B = (Decimal) %d  gives result (Decimal) %d .\n\n", ac_a, ac_b, ac_result);

	printBinaryFormOfNumber(ac_a);
	printBinaryFormOfNumber(ac_b);
	printBinaryFormOfNumber(ac_result);
	
	return(0);
}

int printBinaryFormOfNumber(unsigned int decimal_number)
{
	//variable declarations
	unsigned int quotient, remainder;
	unsigned int num;
	unsigned int binary_array[8];
	int i;
	
	//code
	for (i = 0; i < 8; i++)
	binary_array[i] = 0;

	printf("The binary form of the decimal integer %d is\t= ", decimal_number);
	num = decimal_number;
	i = 7;
	
	while (num != 0)
	{
	quotient = num / 2;
	remainder = num % 2;
	binary_array[i] = remainder;
	num = quotient;
	i--;
	}
	
	for (i = 0; i < 8; i++)
	printf("%u", binary_array[i]);
	
	printf("\n\n");
	return(0);
}
