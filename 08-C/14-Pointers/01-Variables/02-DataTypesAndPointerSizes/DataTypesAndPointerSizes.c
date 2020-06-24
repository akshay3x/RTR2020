#include <stdio.h>

struct Employee
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
	printf("\n\n");
	printf("Displaying sizes of Data Types and corresponding Pointers\n");
	
	printf("sizeof(int) =		%d \nsizeof(int*) =		%d\n\n", sizeof(int), sizeof(int*));
	printf("sizeof(float) =		%d \nsizeof(float*) =	%d\n\n", sizeof(float), sizeof(float*));
	printf("sizeof(double) =	%d	 \nsizeof(double*) =	%d\n\n", sizeof(double), sizeof(double*));
	printf("sizeof(char) =		%d \nsizeof(char*) = 	%d\n\n", sizeof(char), sizeof(char*));

	printf("sizeof(struct Employee) =	%d \nsizeof(struct Employee*) =	%d\n\n", sizeof(struct Employee), sizeof(struct Employee*));
	
	return (0);

}