#include <stdio.h>

int main(void)
{
	//function prototypes
	int printBinaryFormOfNumber(unsigned int);
	
	//variable declarations
	unsigned int ac_a;
	unsigned int ac_num_bits;
	unsigned int ac_result;

	//code
	printf("Enter an integer(A) = ");
	scanf("%u", &ac_a);
	
	printf("\n");
	printf("By how many Bits do you want to shift A = %d to the right ? ", ac_a);
	scanf("%u", &ac_num_bits);

	printf("\n\n");
	ac_result = ac_a >> ac_num_bits;
	printf("Bitwise right-SHIFTing A = %d by %d bits \ngives the result = (Decimal) %d.\n\n", ac_a, ac_num_bits, ac_result);

	printBinaryFormOfNumber(ac_a);
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