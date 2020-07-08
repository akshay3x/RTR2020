#include <stdio.h>

int main(void)
{
	//function declarations
	int AddIntegers(int, int);
	int SubtractIntegers(int, int);
	float AddFloats(float, float);

	//variable declarations
	typedef int (*AddIntsFnPtr)(int, int);
	AddIntsFnPtr ptrAddTwoIntegers = NULL;
	AddIntsFnPtr ptrFn = NULL;

	typedef float (*AddFloatsFnPtr)(float, float);
	AddFloatsFnPtr ptrAddTwoFloats = NULL;

	int iAnswer = 0;
	float fAnswer = 0;

	//code
	ptrAddTwoIntegers = AddIntegers;
	iAnswer = ptrAddTwoIntegers(10, 30);
	printf("\n");
	printf("Sum Of Integers = %d\n", iAnswer);

	ptrFn = SubtractIntegers;
	iAnswer = ptrFn(10, 30);
	printf("\n");
	printf("Subtraction Of Integers = %d\n", iAnswer);

	ptrAddTwoFloats = AddFloats;
	fAnswer = ptrAddTwoFloats(10.0001, 3.0);
	printf("\n");
	printf("Sum Of Floats = %f\n", fAnswer);

	return(0);
}

int AddIntegers(int a, int b)
{
	return(a + b);
}

int SubtractIntegers(int a, int b)
{
	if(a > b)
	return(a - b);
	else
	return(b - a); 
}

float AddFloats(float a, float b)
{
	return(a + b);
}
