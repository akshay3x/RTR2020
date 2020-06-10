#include <stdio.h> 

int main(void)
{
	//function prototype / declaration / signature
	int Ac_MyAddition(void);

	//variable declarations : local to main()
	int ac_result;

	//code
	ac_result = Ac_MyAddition(); //function call

	printf("\n");
	printf("Sum = %d\n ", ac_result);

	return (0);
}

	int Ac_MyAddition(void) //function definition
	{
	//variable declarations : local to Ac_MyAddition()
	int ac_a, ac_b, ac_sum;

	//code
	printf("\n");
	printf("Enter integer value A:");
	scanf("%d", &ac_a);

	printf("\n");
	printf("Enter integer value B:");
	scanf("%d", &ac_b);

	ac_sum = ac_a + ac_b;

	return(ac_sum);
}
