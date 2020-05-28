#include <stdio.h>
int main(void)
{
	int a = 13;
	char ch = 'A';
	long num = 30121995L;
	char str[] = "AstroMediComp's Real Time Rendering Batch 3.0 (2020-2021)";
	unsigned int b = 7;
	float f_num = 3012.1995f;
	double d_pi = 3.14159265358979323846;
	
	//code
    printf("\n\n");
    printf("**************************************************************************************");
    printf("\n\n");

    printf("Hello World !!!\n\n");

	
	printf("Integer Decimal Value Of 'a' = %d\n", a);
	printf("Integer Octal Value Of 'a' = %o\n", a);
	printf("Integer Hexadecimal Value Of 'a' (Hexadecimal Letters In Lower Case) = %x\n", a);
	printf("Integer Hexadecimal Value Of 'a' (Hexadecimal Letters In Lower Case) = %X\n\n", a);

	
	printf("Character ch = %c\n", ch);
	
	printf("String str = %s\n\n", str);

	
	printf("Long Integer = %ld\n\n", num);

	
	printf("Unsigned Integer 'b' = %u\n\n", b);

	
	printf("Floating Point Number With Just %%f 'f_num' = %f\n", f_num);
	printf("Floating Point Number With %%4.2f 'f_num' = %4.2f\n", f_num);
	printf("Floating Point Number With %%6.5f 'f_num' = %6.5f\n\n", f_num);

	
	printf("Double Precision Floating Point Number Without Exponential = %g\n", d_pi);
	printf("Double Precision Floating Point Number With Exponential (Lower Case) = %e\n", d_pi);
	printf("Double Precision Floating Point Number With Exponential (Upper Case) = %E\n\n", d_pi);
	printf("Double Hexadecimal Value Of 'd_pi' (Hexadecimal Letters In Lower Case) = %a\n", d_pi);
	printf("Double Hexadecimal Value Of 'd_pi' (Hexadecimal Letters In Upper Case) = %A\n\n", d_pi);
    
    printf("**************************************************************************************\n");
    printf("\n\n");
	return(0);
}
