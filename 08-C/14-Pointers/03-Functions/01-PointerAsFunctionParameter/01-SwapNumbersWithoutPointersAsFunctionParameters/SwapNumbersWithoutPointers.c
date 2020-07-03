#include <stdio.h>

int main(void)
{
	//function declarations
	void AC_SwapNumbers(int, int);

	//variable declarations
	int ac_a;
	int ac_b;

	//code
	printf("\n");
	printf("Enter integer value for A:");
	scanf("%d", &ac_a);

	printf("\n");
	printf("Enter integer value for B:");
	scanf("%d", &ac_b);

	//before swap
	printf("\n\n");
	printf("--- Before Swapping in main() ---\n");
	printf("Value A: %d\n", ac_a);
	printf("Value B: %d\n", ac_b);

	//swapping function call
	AC_SwapNumbers(ac_a, ac_b);

	printf("\n\n");
	printf("--- After Swapping in main() ---\n");
	printf("Value A: %d\n", ac_a);
	printf("Value B: %d\n", ac_b);

	return (0);
}


void AC_SwapNumbers(int ac_x, int ac_y)
{
	//variable declarations
	int temp;

	//code
	printf("\n\n");
	printf("--- Before Swapping in Swap() ---\n");
	printf("Value A: %d\n", ac_x);
	printf("Value B: %d\n", ac_y);

	//swapping logic
	temp = ac_x;
	ac_x = ac_y;
	ac_y = temp;

	printf("\n\n");
	printf("--- After Swapping in Swap() ---\n");
	printf("Value A: %d\n", ac_x);
	printf("Value B: %d\n", ac_y);
}
