#include <stdio.h>

	//defining structure
	struct MyData
	{
		int i;
		float f;
		double d;
		char c;
	};

int main(void)
{
	//declaring local structure variable
	struct MyData data;

	//variable declarations
	int i_size;
	int f_size;
	int d_size;
	int c_size;
	char c;
	int struct_MyData_size;

	//code
	data.i = 450;
	data.f = 19.988;
	data.d = 12123.34555;
	data.c = 'A';

	printf("\n");
	printf("Displaying Structure members\n"); 
	printf("data.i = %d\n", data.i);
	printf("data.f = %f\n", data.f);
	printf("data.d = %lf\n", data.d);
	printf("data.c = %c\n", data.c);

	i_size = sizeof(data.i);
	f_size = sizeof(data.f);
	d_size = sizeof(data.d);
	c_size = sizeof(data.c);

	printf("\n");
	printf("Sizes:\n");
	printf("Size of i = %d bytes\n", i_size);
	printf("Size of f = %d bytes\n", f_size);
	printf("Size of d = %d bytes\n", d_size);
	printf("Size of c = %d bytes\n", c_size);
	
	printf("\n");
	struct_MyData_size = sizeof(struct MyData);
	printf("Size of struct MyData = %d\n", struct_MyData_size);

	return (0);
}
