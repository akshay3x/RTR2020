#include <stdio.h>

#define AC_MAX_NUMBER(a, b) ((a > b) ? a : b)

int main(int argc, char *argv[], char *envp[])
{
	// variable declarations
	int iac_Num_01;
	int iac_Num_02;
	int iac_Result;

	float fac_Num_01;
	float fac_Num_02;
	float fac_Result;

	// code
	printf("\n");
	printf("Enter 1st Integer Number A:");
	scanf("%d", &iac_Num_01);

	printf("\n");
	printf("Enter 2nd Integer Number B:");
	scanf("%d", &iac_Num_02);

	iac_Result = AC_MAX_NUMBER(iac_Num_01, iac_Num_02);

	printf("\n\n");
	printf("Result Of Macro Function MAX_NUMBER() = %d\n", iac_Result);
	printf("\n");


	printf("\n");
	printf("Enter 1st Floating Point Number :");
	scanf("%f", &fac_Num_01);

	printf("\n");
	printf("Enter 2nd Floating Point Number :");
	scanf("%f", &fac_Num_02);

	fac_Result = AC_MAX_NUMBER(fac_Num_01, fac_Num_02);

	printf("\n");
	printf("Result Of Macro Function MAX_NUMBER() = %f\n", fac_Result);
	printf("\n");

	return(0);
}
