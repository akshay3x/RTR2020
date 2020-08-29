#include <stdio.h>
#include <stdarg.h>

//macro definitions
#define NUM_TO_BE_FOUND		3
#define NUM_ELEMENTS		10

int main(void)
{
	//function declarations
	void FindNumber(int, int, ...);

	//code
	printf("\n\n");
	FindNumber(NUM_TO_BE_FOUND, NUM_ELEMENTS, 3, 5, 9, 2, 3, 6, 9, 3, 1, 3);

	return(0);
}

void FindNumber(int num_to_be_found, int num, ...)
{
	//variable declarations
	int count = 0;
	int n;
	va_list number_list;

	//code
	va_start(number_list, num);

	while(num)
	{
		n = va_arg(number_list, int);
		if(n == num_to_be_found)
			count++;
		num--;
	}

	if(count == 0)
		printf("Number %d could not be found!\n", num_to_be_found);
	else
		printf("Number %d found %d times!\n", num_to_be_found, count);

	va_end(number_list);
}