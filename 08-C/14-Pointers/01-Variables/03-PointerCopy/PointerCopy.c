#include <stdio.h>

int main()
{
	//variable declarations
	int num;
	int *ptr = NULL;
	int *copy_ptr = NULL;

	//code
	num = 100;
	ptr = &num;

	printf("\n\n");
	printf("--- Before copy_ptr = ptr ---\n");
	printf(" num =		%d\n", num);
	printf(" &num =		%P\n", &num);
	printf(" *(&num) =	%d\n", *(&num));
	printf(" ptr =		%p\n", ptr);
	printf(" *ptr =		%d\n", *ptr);
	
	copy_ptr = ptr;
	//both ptr and copy_ptr points to num now
	
	printf("\n\n");
	printf("--- After copy_ptr = ptr ---\n");
	printf(" num =		%d\n", num);
	printf(" &num =		%P\n", &num);
	printf(" *(&num) =	%d\n", *(&num));
	printf(" ptr =		%p\n", ptr);
	printf(" *ptr =		%d\n", *ptr);
	printf(" copy_ptr =	%p\n", copy_ptr);
	printf(" *copy_ptr =	%d\n", *copy_ptr);
	
	return (0);
}

