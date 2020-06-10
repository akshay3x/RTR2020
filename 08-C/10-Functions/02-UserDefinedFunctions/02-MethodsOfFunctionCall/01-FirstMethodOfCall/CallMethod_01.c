#include <stdio.h> 

int main(void)
{
	//function prototypes OR declarations
	void Ac_MyAddition(void);
	int Ac_MySubtraction(void);
	void Ac_MyMultiplication(int, int);
	int Ac_MyDivision(int, int);

	//variable declarations
	int ac_result_subtraction;
	int ac_a_multiplication, ac_b_multiplication;
	int ac_a_division, ac_b_division, ac_result_division;

	//code
	// ADDITION 
	Ac_MyAddition(); //function call

	// SUBTRACTION 
	ac_result_subtraction = Ac_MySubtraction(); //function call

	printf("\n\n");
	printf("Subtraction Result = %d\n", ac_result_subtraction);

	// MULTIPLICATION 
	printf("\n");
	printf("Enter integer value A: For Multiplication:");
	scanf("%d", &ac_a_multiplication);

	printf("\n");
	printf("Enter integer value A: For Multiplication:");
	scanf("%d", &ac_b_multiplication);

	Ac_MyMultiplication(ac_a_multiplication, ac_b_multiplication); //function call

	// DIVISION 
	printf("\n\n");
	printf("Enter integer value A: For Division : ");
	scanf("%d", &ac_a_division);

	printf("\n\n");
	printf("Enter integer value B: For Division : ");
	scanf("%d", &ac_b_division);

	ac_result_division = Ac_MyDivision(ac_a_division, ac_b_division); //function call
	printf("\n\n");
	printf(" %d / %d = %d (Quotient)\n", ac_a_division, ac_b_division, ac_result_division);
	printf("\n\n");

	return(0);
}

void Ac_MyAddition(void) //function definition
{
	//variable declarations : local variables to MyAddition()
	int ac_a, ac_b, ac_sum;

	//code
	printf("\n");
	printf("Enter integer value A: For Addition : ");
	scanf("%d", &ac_a);

	printf("\n\n");
	printf("Enter integer value B: For Addition : ");
	scanf("%d", &ac_b);

	ac_sum = ac_a + ac_b;

	printf("\n\n");
	printf(" %d + %d = %d\n\n", ac_a, ac_b, ac_sum);
}


// Function Definition Of MySubtraction() 
int Ac_MySubtraction(void) //function definition
{
	//variable declarations : local variables to MySubtraction()
	int ac_a, ac_b, ac_subtraction;

	//code
	printf("\n\n");
	printf("Enter integer value A: For Subtraction : ");
	scanf("%d", &ac_a);

	printf("\n\n");
	printf("Enter integer value B: For Subtraction : ");
	scanf("%d", &ac_b);

	ac_subtraction = ac_a - ac_b;

	return(ac_subtraction);
}

void Ac_MyMultiplication(int ac_a, int ac_b) //function definition
{
	//variable declarations : local variables to MyMultiplication()
	int ac_multiplication;

	//code
	ac_multiplication = ac_a * ac_b;
	
	printf("\n\n");
	printf(" %d * %d = %d \n\n", ac_a, ac_b, ac_multiplication);

}


int Ac_MyDivision(int ac_a, int ac_b) //function definition
{
	//variable declarations : local variables to MyDivision()
	int ac_division_quotient;

	//code
	if (ac_a > ac_b)
		ac_division_quotient = ac_a / ac_b;
	
	else
		ac_division_quotient = ac_b / ac_a;

	return(ac_division_quotient);

}

