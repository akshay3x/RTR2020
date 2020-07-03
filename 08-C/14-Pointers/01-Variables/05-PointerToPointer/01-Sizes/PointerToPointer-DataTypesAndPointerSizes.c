#include <stdio.h>

//stucture
struct Emp_Record
{
	char name[100];
	int age;
	float salary;
	char sex;
	char marital_status;
};

int main(void)
{
	//code
	//int
	printf("\n\n");
	printf("Sizes and data types are:\n\n");
	printf("--- int ---\n");
	printf("Size of int = %d\n", sizeof(int));
	printf("Size of pointer to int = %d\n", sizeof(int*));
	printf("Size of pointer to pointer to int = %d\n", sizeof(int**));

	//float
	printf("\n\n");
	printf("--- float ---\n");
	printf("Size of float = %d\n", sizeof(float));
	printf("Size of pointer to float = %d\n", sizeof(float*));
	printf("Size of pointer to pointer to float = %d\n", sizeof(float**));

	//double
	printf("\n\n");
	printf("--- double ---\n");
	printf("Size of double = %d\n", sizeof(double));
	printf("Size of pointer to double = %d\n", sizeof(double*));
	printf("Size of pointer to pointer to double = %d\n", sizeof(double**));

	//char
	printf("\n\n");
	printf("--- char ---\n");
	printf("Size of char = %d\n", sizeof(char));
	printf("Size of pointer to char = %d\n", sizeof(char*));
	printf("Size of pointer to pointer to char = %d\n", sizeof(char**));

	//stuct employee record
	printf("\n\n");
	printf("--- Emp_Record ---\n");
	printf("Size of Struct Emp_Record = %d\n", sizeof(struct Emp_Record));
	printf("Size of pointer to Emp_Record = %d\n", sizeof(struct Emp_Record*));
	printf("Size of pointer to pointer to Emp_Record = %d\n", sizeof(struct Emp_Record**));

	return (0);
}
