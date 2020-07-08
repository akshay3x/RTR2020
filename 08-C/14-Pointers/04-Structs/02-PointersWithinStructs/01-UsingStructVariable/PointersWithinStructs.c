#include <stdio.h>

//defining struct
struct Mydata
{
	int *ptr_ix;
	int ix;

	float *ptr_fy;
	float fy;

	double *ptr_dz;
	double dz;
};

int main(void)
{
	//variable declaration
	struct Mydata data;

	//code
	//assigning values
	data.ix = 11;
	data.ptr_ix = &data.ix;

	data.fy = 12.12f;
	data.ptr_fy = &data.fy;

	data.dz = 13.1313;
	data.ptr_dz = &data.dz;

	//displaying values
	printf("\n\n");
	printf("ix = 		%d\n", data.ix);
	printf("ix = 		%d\n", *(data.ptr_ix));
	printf("Address = 	%p\n", data.ptr_ix);
	
	printf("\n\n");
	printf("fy = 		%f\n", data.fy);
	printf("fy = 		%f\n", *(data.ptr_fy));
	printf("Address = 	%p\n", data.ptr_fy);

	printf("\n\n");
	printf("dz = 		%lf\n", data.dz);
	printf("dz = 		%lf\n", *(data.ptr_dz));
	printf("Address = 	%p\n", data.ptr_dz);

	return(0);
}
