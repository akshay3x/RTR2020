#include <stdio.h> 

int main(void)
{
	//function prototype / declaration / signature
	void Ac_MyAddition(int, int);

	//variable declarations : local to main()
	int ac_a, ac_b;

	//code
	printf("\n");
	printf("Enter integer value A:");
	scanf("%d", &ac_a);

	printf("\n");
	printf("Enter integer value B:");
	scanf("%d", &ac_b);

	Ac_MyAddition(ac_a, ac_b); 
	return(0);
}

void Ac_MyAddition(int ac_x, int ac_y) //function definition
{
	//variable declarations : local to MyAddition()
	int ac_sum;

	//code
	ac_sum = ac_x + ac_y;
	printf("\n\n");

	printf(" %d + %d = %d\n\n", ac_x, ac_y, ac_sum);
}
