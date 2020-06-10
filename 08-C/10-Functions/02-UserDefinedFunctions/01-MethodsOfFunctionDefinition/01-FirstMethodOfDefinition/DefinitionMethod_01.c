#include <stdio.h> 

int main(int argc, char *argv[], char *envp[])
{
	//function prototype / declaration / signature
	void Ac_MyAddition(void);

	//code
	Ac_MyAddition(); //function call
	
	return(0);
}

void Ac_MyAddition(void) //function definition
{
	//variable declarations : local to MyAddition()
	int ac_a, ac_b, ac_sum;

	//code
	printf("\n");
	printf("Enter Integer Value A: ");
	scanf("%d", &ac_a);

	printf("\n");
	printf("Enter Integer Value B: ");
	scanf("%d", &ac_b);

	ac_sum = ac_a + ac_b;
	printf("\n");
	printf("Sum Of %d And %d = %d\n\n", ac_a, ac_b, ac_sum);
}
