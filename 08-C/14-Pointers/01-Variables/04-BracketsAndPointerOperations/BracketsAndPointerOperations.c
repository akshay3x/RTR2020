#include <stdio.h>

int main(void)
{
	//variable declarations
	int num;
	int *ptr = NULL;
	int ans;

	//code
	num = 5;
	ptr = &num;

	printf("\n");
	printf(" num =		%d\n", num);
	printf(" &num =		%p\n", &num);
	printf(" *(&num) =	%d\n",*(&num));
	printf(" ptr =		%p\n", ptr);
	printf(" *ptr =		%d\n", *ptr);

	printf("\n\n");

	printf(" (ptr + 10) =	%p\n", (ptr + 10));

	printf(" *(ptr + 10) =	%d\n", *(ptr + 10));

	printf(" (*ptr + 10) =	%d\n", (*ptr + 10));

	++*ptr;
	printf(" ++*ptr =	%d\n", *ptr);

	*ptr++;
	printf(" *ptr++ =	%d\n", *ptr);

	ptr = &num;
	(*ptr)++;
	printf(" (*ptr)++ =	%d\n", *ptr);

	return (0);
}
