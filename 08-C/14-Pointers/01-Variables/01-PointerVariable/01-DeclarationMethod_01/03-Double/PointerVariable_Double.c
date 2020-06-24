#include <stdio.h>

int main(void)
{
	//variable declarations
	double num;
	double *ptr = NULL;
	
	//code
	num = 11.0991245123f;
	
	printf("\n");
	printf("--- Before ptr = &num ---\n");
	printf("Value of num = 		%lf\n", num);
	printf("Address of Num = 	%p\n", &num);
	printf("Value At Address of num = %lf\n", *(&num));

	//pointer assignment
	ptr = &num;
	
	printf("\n\n");
	printf("--- After ptr = &num ---\n");
	printf("Value of num = 		%lf\n", num);
	printf("Address in ptr	 = 	%p\n", &num);
	printf("Value At ptr = 		%lf\n", *ptr);

	return (0);
}

