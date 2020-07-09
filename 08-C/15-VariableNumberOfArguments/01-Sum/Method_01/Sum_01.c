#include <stdio.h>
#include <stdarg.h>

int main(void)
{
	//function declarations
	int CalculateSum(int, ...);

	//variable declarations
	int answer;

	//code
	printf("\n\n");
	answer = CalculateSum(3, 9, 10, 11);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(4, 9, 10, 11, 12);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(5, 9, 10, 11, 12, 13);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(6, 9, 10, 11, 12, 13, 14);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(0);
	printf("answer = %d\n\n", answer);

	return(0);
}

int CalculateSum(int num, ...)
{
	//variable declarations
	int sum_total = 0;
	int n;

	va_list number_list;

	//code
	va_start(number_list, num);

	while(num)
	{
		n = va_arg(number_list, int);
		sum_total = sum_total + n;
		num--;
	}

	va_end(number_list);

	return(sum_total);
}
