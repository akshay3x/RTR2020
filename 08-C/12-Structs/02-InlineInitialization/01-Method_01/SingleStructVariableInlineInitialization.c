#include <stdio.h>

//defining structure
struct AcMydata
{
	int ix;
	float fy;
	double dz;
	char ca;
} data = {12, 13.44f, 12.4567323, 'A'};

int main()
{
	printf("Displaying Sructure Members\n\n");

	printf("data.ix = %d\n", data.ix);
	printf("data.fy = %f\n", data.fy);
	printf("data.dz = %lf\n", data.dz);
	printf("data.ca = %c\n", data.ca);

	printf("\n");

	return (0);
}