#include <stdio.h>

int main(void)
{
	//variable declarations
	int num;
	int *ptr = NULL;
	
	//code
	num = 100;
	
	printf("\n");
	printf("--- Before ptr = &num ---\n");
	printf("Value of num = 		%d\n", num);
	printf("Address of Num = 	%p\n", &num);
	printf("Value At Address of num = %d\n", *(&num));

	//pointer assignment
	ptr = &num;
	
	printf("\n\n");
	printf("--- After ptr = &num ---\n");
	printf("Value of num = 		%d\n", num);
	printf("Address in ptr = 	%p\n", ptr);
	printf("Value At ptr = 		%d\n", *ptr);

	return (0);
}

