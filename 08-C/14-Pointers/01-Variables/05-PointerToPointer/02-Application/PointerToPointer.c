#include <stdio.h>

int main(void)
{
	//variable declarations
	int num;
	int *ptr = NULL;
	int **pptr = NULL;

	//code
	num = 10;

	//before assigning address of variable to pointer
	printf("\n\n");
	printf("--- Before ptr = &num ---\n");
	printf("value of num = 				%d\n", num);
	printf("address of num (&num) =			%p\n", &num);
	printf("value at address of num (*(&num))= 	%d\n", *(&num));

	//assigning address of variable to pointer
	ptr = &num;

	//after assigning address of variable to pointer
	printf("\n\n");
	printf("--- Before ptr = &num ---\n");
	printf("value of num = 				%d\n", num);
	printf("address of num (ptr) = 			%p\n", ptr);
	printf("value at address of num (*ptr) = 	%d\n", *ptr);

	//assigning address of pointer to pointer to pointer variable
	pptr = &ptr;

	//after assigning address of pointer to pointer to pointer variable
	printf("\n\n");
	printf("--- After pptr = &ptr ---\n");
	printf("value of num = 					%d\n", num);
	printf("addres of num (ptr) =				%p\n", ptr);
	printf("address of ptr (pptr) = 			%p\n", pptr);
	printf("value at address of ptr (*pptr)=		%p\n", *pptr);
	printf("value at address of num(*ptr) or (**pptr) = 	%d\n", **pptr);

	return (0);
}
