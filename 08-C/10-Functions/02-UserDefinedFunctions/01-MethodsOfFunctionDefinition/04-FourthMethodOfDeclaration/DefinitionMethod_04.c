#include <stdio.h> 

int main(void)
{

	//function prototype / declaration / signature
	int Ac_MyAddition(int, int);

	//variable declarations : local to main()
	int ac_a, ac_b, ac_result;

	//code
	printf("\n");
	printf("Enter Integer Value A:");
	scanf("%d", &ac_a);

	printf("\n");
	printf("Enter Integer Value B:");
	scanf("%d", &ac_b);

	ac_result = Ac_MyAddition(ac_a, ac_b); //function call

	printf("\n");
	printf(" %d + %d = %d\n\n", ac_a, ac_b, ac_result);

	return(0);
}


int Ac_MyAddition(int ac_a, int ac_b) //function definition
{
	//variable declarations : local to MyAddition()
	int ac_sum;

	//code
	ac_sum = ac_a + ac_b;

	return(ac_sum);
}
