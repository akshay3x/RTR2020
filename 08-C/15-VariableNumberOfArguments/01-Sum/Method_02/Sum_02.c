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

	answer = CalculateSum(20, 21, 22);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(20, 21, 22, 23);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(20, 21, 22, 23, 24);
	printf("answer = %d\n\n", answer);

	answer = CalculateSum(0);
	printf("answer = %d\n\n", answer);

	return(0);
}

int CalculateSum(int num, ...)
{
	//function declarations
	int va_CalculateSum(int, va_list);

	//variable declarations
	int sum = 0;
	va_list number_list;

	//code
	va_start(number_list, num);

	sum = va_CalculateSum(num, number_list);

	va_end(number_list);
	return(sum);
}

int va_CalculateSum(int num, va_list list)
{
	int n;
	int sum = 0;

	//code
	while(num)
	{
		n = va_arg(list, int);
		sum = sum + n;
		num--;
	}

	return(sum);
}
