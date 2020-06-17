#include <stdio.h>

	//defining structure
	struct AcMyData
	{
		int ix;
		float fy;
		double dz;
		char ca;
	};


int main(void)
{

	struct AcMyData x = {12, 56.78, 23324.7889, 'C'};
	
	struct AcMyData y = {'C', 56.78, 23324.7889, 75};
	
	struct AcMyData z = {59, '*'};
	
	struct AcMyData w = {12.79};
	
	printf("\n");
	printf("Displaying Sructure Members of x\n");

	printf("x.ix = %d\n", x.ix);
	printf("x.fy = %f\n", x.fy);
	printf("x.dz = %lf\n", x.dz);
	printf("x.ca = %c\n", x.ca);

	printf("\n");
	printf("Displaying Sructure Members of y\n");

	printf("y.ix = %d\n", y.ix);
	printf("y.fy = %f\n", y.fy);
	printf("y.dz = %lf\n", y.dz);
	printf("y.ca = %c\n", y.ca);

	printf("\n");
	printf("Displaying Sructure Members of z\n");

	printf("z.ix = %d\n", z.ix);
	printf("z.fy = %f\n", z.fy);
	printf("z.dz = %lf\n", z.dz);
	printf("z.ca = %c\n", z.ca);

	printf("\n");
	printf("Displaying Sructure Members of w\n");

	printf("w.ix = %d\n", w.ix);
	printf("w.fy = %f\n", w.fy);
	printf("w.dz = %lf\n", w.dz);
	printf("w.ca = %c\n", w.ca);

	return (0);
}