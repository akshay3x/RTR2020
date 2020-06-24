#include <stdio.h>

//structure declarations
struct AC_Mydata
{
	int ix;
	float fy;
	double dz;
	char cw;
};

int main(void)
{

	//variable declarations
	struct AC_Mydata data;

	//code
	data.ix = 45;
	data.fy = 12.123;
	data.dz = 123.987;
	data.cw = 'A';

	printf("\n\n");
	printf("Displaying Data:\n");
	printf(" x = %d\n", data.ix);
	printf(" f = %f\n", data.fy);
	printf(" d = %lf\n", data.dz);
	printf(" c = %c\n", data.cw);

	printf("\n\n");
	printf("Displaying Addresses:\n");
	printf(" x is at address = %p\n", &data.ix);
	printf(" f is at address = %p\n", &data.fy);
	printf(" d is at address = %p\n", &data.dz);
	printf(" c is at address = %p\n", &data.cw);

	printf("\n");
	printf(" 'struct Mydata data' is at address = %p\n", &data);

	return (0);
}
