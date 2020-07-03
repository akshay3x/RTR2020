#include <stdio.h>

//enum declaration
enum
{
	NEGATIVE = -1,
	ZERO,
	POSITIVE
};

int main(void)
{
	//function declarations
	int check_diff(int, int, int *);

	//variable declarations
	int ac_a;
	int ac_b;
	int ans, ret;

	//code
	printf("\n\n");
	printf("Enter integer value for A: ");
	scanf("%d", &ac_a);

	printf("\n\n");
	printf("Enter integer value for B: ");
	scanf("%d", &ac_b);

	//function call
	ret = check_diff(ac_a, ac_b, &ans);

	//displaying results
	printf("\n");
	printf("Difference of %d and %d = %d\n\n", ac_a, ac_b, ans);

	if(ret == POSITIVE)
		printf("Diifernce is Positive\n");
	else if(ret == NEGATIVE)
		printf("Diifernce is Negative\n");
	else
		printf("Difference is Zero\n");

	return(0);
}


int check_diff(int ac_x, int ac_y, int *diff)
{
	//code
	*diff = ac_x - ac_y;

	if(*diff > 0)
		return(POSITIVE);
	if(*diff < 0)
		return(NEGATIVE);
	else
		return(ZERO);
}
