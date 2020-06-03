#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_i, ac_j;
	char ac_ch_01, ac_ch_02;

	int ac_a, ac_result_int;
	float ac_f, ac_result_float;

	int ac_i_explicit;
	float ac_f_explicit;

	//code
	printf("\n\n----IMPLICITE CONVERSIONS----\n");
	printf("---char <--> int--- \n");
	printf("1.'int' --> 'char'\n\n");

	ac_i = 77;
	ac_ch_01 = ac_i;

	printf("Integer Value =\t %d\n", ac_i);
	printf("Conversion value  = %c \n\n\n", ac_ch_01);


	printf("2.'char' --> 'int'\n\n");

	ac_ch_02 = 'D';
	ac_j = ac_ch_02;

	printf("Charater = \t%c\n", ac_ch_02);
	printf("Conversion to Integer = %d\n\n\n", ac_j);
	printf("----------------------------\n\n");
	
	printf("---float <--> int ---\n");
	printf("1.'int' --> 'float'\n\n");
	
	ac_a = 7;
	ac_f = 6.8f;

	ac_result_float = ac_a + ac_f;
	printf("Integer A = %d + Float F = %f  = %f \n\n", ac_a, ac_f, ac_result_float);
	
	printf("2.'float' --> 'int'\n\n");
	ac_result_int = ac_a + ac_f;
	printf("Integer A = %d + Float F = %f  = %d\n", ac_a, ac_f, ac_result_int);
	printf("\n--------------------------------------\n");
	
	printf("\n----EXPLICITE CONVERSIONS----\n");
	ac_f_explicit = 409.121995123f;
	ac_i_explicit = (int)ac_f_explicit;
	printf("Floating Point Number F = %f\n", ac_f_explicit);
	printf("Explicit Type Casting   = %d\n\n", ac_i_explicit);

	return(0);
}
