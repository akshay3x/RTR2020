#include <stdio.h>

int main(void)
{
	//variable declarations
	float num;
	float *ptr = NULL;
	
	//code
	num = 69.099;
	
	printf("\n");
	printf("--- Before ptr = &num ---\n");
	printf("Value of num = 		%f\n", num);
	printf("Address of Num = 	%p\n", &num);
	printf("Value At Address of num = %f\n", *(&num));

	//pointer assignment
	ptr = &num;
	
	printf("\n\n");
	printf("--- After ptr = &num ---\n");
	printf("Value of num = 		%f\n", num);
	printf("Address in ptr = 	%p\n", ptr);
	printf("Value At ptr = 		%f\n", *ptr);

	return (0);
}

