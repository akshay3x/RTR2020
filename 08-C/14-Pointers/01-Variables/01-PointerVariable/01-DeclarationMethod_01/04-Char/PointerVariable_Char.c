#include <stdio.h>

int main(void)
{
	//variable declarations
	char c;
	char *ptr = NULL;
	
	//code
	c = 'A';
	
	printf("\n");
	printf("--- Before ptr = &c ---\n");
	printf("Value of c = 		%c\n", c);
	printf("Address of c = 		%p\n", &c);
	printf("Value At Address of c = %c\n", *(&c));

	//pointer assignment
	ptr = &c;
	
	printf("\n\n");
	printf("--- After ptr = &c ---\n");
	printf("Value of c = 		%c\n", c);
	printf("Address in ptr = 	%p\n", ptr);
	printf("Value At ptr = 		%c\n", *ptr);

	return (0);
}

