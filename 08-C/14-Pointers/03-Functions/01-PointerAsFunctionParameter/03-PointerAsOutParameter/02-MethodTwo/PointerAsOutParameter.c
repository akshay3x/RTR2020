#include <stdio.h>

int main(void)
{
	//function declaration
	void MathOperations(int, int, int*, int*, int*, int*, int*);

	//variable declarations
	int ac_a, ac_b;
	int *ans_sum = NULL;
	int *ans_diff = NULL;
	int *ans_product = NULL;
	int *ans_quotient = NULL;
	int *ans_remainder = NULL;

	//code
	//user input values
	printf("\n\n");
	printf("Enter integer value for A: ");
	scanf("%d", &ac_a);

	printf("\n\n");
	printf("Enter integer value for B: ");
	scanf("%d", &ac_b);

	//memory allocation
	ans_sum = (int*) malloc(sizeof(int));
	if(ans_sum == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for ans_sum\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation successful for the ans_sum\n");
	}

	//memory allocation
	ans_diff = (int*) malloc(sizeof(int));
	if(ans_diff == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for ans_diff\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation successful for the ans_diff\n");
	}

	//memory allocation
	ans_product = (int*) malloc(sizeof(int));
	if(ans_product == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for ans_product\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation successful for the ans_product\n");
	}

	//memory allocation
	ans_quotient = (int*) malloc(sizeof(int));
	if(ans_quotient == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for ans_quotient\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation successful for the ans_quotient\n");
	}

	//memory allocation
	ans_remainder = (int*) malloc(sizeof(int));
	if(ans_remainder == NULL)
	{
		printf("\n");
		printf("Memory Allocation failed for ans_remainder\nExiting...\n\n");
		exit(0);
	}

	else
	{
		printf("\n");
		printf("Memory Allocation successful for the ans_remainder\n");
	}

	//function call
	MathOperations(ac_a, ac_b, ans_sum, ans_diff, ans_product, ans_quotient, ans_remainder);

	//displaying results
	printf("\n\n");
	printf("--- Results ---\n");
	printf("Sum =		%d\n", *ans_sum);
	printf("Difference =	%d\n", *ans_diff);
	printf("Product =	%d\n", *ans_product);
	printf("Quotient =	%d\n", *ans_quotient);
	printf("Remainder =	%d\n\n", *ans_remainder);

	//freeing allocated memory
	if(ans_remainder)
	{
		free(ans_remainder);
		ans_remainder = NULL;
		printf("Memory freed: ans_remainder\n");
	}

	if(ans_quotient)
	{
		free(ans_quotient);
		ans_quotient = NULL;
		printf("Memory freed: ans_quotient\n");
	}

	if(ans_product)
	{
		free(ans_product);
		ans_product = NULL;
		printf("Memory freed: ans_product\n");
	}

	if(ans_diff)
	{
		free(ans_diff);
		ans_diff = NULL;
		printf("Memory freed: ans_diff\n");
	}

	if(ans_sum)
	{
		free(ans_sum);
		ans_sum = NULL;
		printf("Memory freed: ans_sum\n");
	}

	return (0);
}

void MathOperations(int x, int y, int *sum, int *diff, int *product, int *quotient, int *remainder)
{
	*sum = x + y;
	*diff = x - y;
	*product = x * y;
	*quotient = x / y;
	*remainder = x % y;
}

