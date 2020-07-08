#include <stdio.h>

//defining structure
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
	//variable declarations
	struct Mydata *pData = NULL;
	
	//code
	//memory allocation
	pData = (struct Mydata *) malloc(sizeof(struct Mydata));
	
	if(pData == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed: pData\n");
		printf("Exiting...\n");
		exit(0);
	}

	else
	{
		printf("\n\n");
		printf("Memory Allocated: pData");
	}

	//assigning values
	pData->ix = 45;
	pData->ptr_ix = &(pData->ix);
	
	pData->fy = 23.23f;
	pData->ptr_fy = &(pData->fy);

	pData->dz = 23.2323;
	pData->ptr_dz = &(pData->dz);

	//displaying values
	printf("\n\n");
	printf("ix = 		%d\n", pData->ix);
	printf("ix = 		%d\n", *(pData->ptr_ix));
	printf("Address = 	%p\n", pData->ptr_ix);

	printf("\n\n");
	printf("fy = 		%f\n", pData->fy);
	printf("fy = 		%f\n", *(pData->ptr_fy));
	printf("Address = 	%p\n", pData->ptr_fy);

	printf("\n\n");
	printf("dz = 		%lf\n", pData->dz);
	printf("dz = 		%lf\n", *(pData->ptr_dz));
	printf("Address = 	%p\n", pData->ptr_dz);

	//freeing memory
	if(pData)
	{
		printf("\n\n");
		printf("Memory Freed: pData");
	}

	return(0);
}
