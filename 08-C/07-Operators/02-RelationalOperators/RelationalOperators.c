#include <stdio.h>
int main(void)
{
	//variable declarations
	int ac_a;
	int ac_b;
	int ac_result;
	
	//code
	printf("Enter 1st integer(A) : ");
	scanf("%d", &ac_a);
	
	printf("\n");
	printf("Enter 2nd integer(B) : ");
	scanf("%d", &ac_b);
	
	printf("\n");
	printf("If Answer = 0, It Is 'FALSE'.\n");
	printf("If Answer = 1, It Is 'TRUE'.\n\n");

	ac_result = (ac_a < ac_b);
	printf("(A < B) \t A=%d is less than B=%d    \t\t answer=%d\n", ac_a, ac_b, ac_result);
	
	ac_result = (ac_a > ac_b);
	printf("(A > B) \t A=%d is greater than B=%d \t\t answer=%d\n", ac_a, ac_b, ac_result);

	ac_result = (ac_a <= ac_b);
	printf("(A <= B)\t A=%d is less than or equal to B=%d \t answer=%d\n", ac_a, ac_b, ac_result);
	
	ac_result = (ac_a >= ac_b);
	printf("(A >= B)\t A=%d is greater than or equal to B=%d \t answer=%d\n", ac_a, ac_b, ac_result);
	
	ac_result = (ac_a == ac_b);
	printf("(A == B)\t A=%d is equal to B=%d     \t\t answer=%d\n", ac_a, ac_b, ac_result);

	ac_result = (ac_a != ac_b);
	printf("(A != B)\t A=%d is not equal to B=%d \t\t answer=%d\n", ac_a, ac_b, ac_result);

	return(0);
}