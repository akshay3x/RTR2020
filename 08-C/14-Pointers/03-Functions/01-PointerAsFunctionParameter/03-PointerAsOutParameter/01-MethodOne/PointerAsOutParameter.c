#include <stdio.h>

int main(void)
{
	//function declarations
	void MathOperations(int, int, int *, int *, int *, int *, int *);

	//variable declarations
	int ac_a;
	int ac_b;
	int ans_sum;
	int ans_diff;
	int ans_product;
	int ans_quotient;
	int ans_remainder;

	//code
	printf("\n\n");
	printf("Enter Integer Value for A: ");
	scanf("%d", &ac_a);

	printf("\n\n");
	printf("Enter Integer Value for B: ");
	scanf("%d", &ac_b);

	//function call
	MathOperations(ac_a, ac_b, &ans_sum, &ans_diff, &ans_product, &ans_quotient, &ans_remainder);

	//displaying results
	printf("\n\n");
	printf("--- Results ---\n");
	printf("Sum = %d\n", ans_sum);
	printf("Difference = %d\n", ans_diff);
	printf("Product = %d\n", ans_product);
	printf("Quoteint = %d\n", ans_quotient);
	printf("Reminder = %d\n", ans_remainder);

	return (0);
}

void MathOperations(int ac_x, int ac_y, int *sum, int *diff, int *prod, int *quotient, int *remainder)
{
	//code
	*sum = ac_x + ac_y;
	*diff = ac_x - ac_y;
	*prod = ac_x * ac_y;
	*quotient = ac_x / ac_y;
	*remainder = ac_x % ac_y;
}

