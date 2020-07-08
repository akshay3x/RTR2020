#include <stdio.h>

//defining struct
struct Mydata
{
	int ix;
	float fy;
	double dz;
};

int main(void)
{
	//function declarations
	void ChangeValues(struct Mydata *);

	//variable declarations
	struct Mydata *pData = NULL;

	//code
	//memory allocations
	pData = (struct Mydata *) malloc(sizeof(struct Mydata));

	if(pData == NULL)
	{
		printf("\n\n");
		printf("Memory Allocation Failed: pData");
		printf("Exiting...\n");
		exit(0);
	}
	else
	{
		printf("\n");
		printf("Memory Allocated:pData\n");
	}

	//assigning values
	pData->ix = 30;
	pData->fy = 11.45f;
	pData->dz = 123.123;

	//displaying values
	printf("\n");
	printf("ix = %d\n", pData->ix);
	printf("fy = %f\n", pData->fy);
	printf("dz = %lf\n", pData->dz);

	//function call
	ChangeValues(pData);

	//displaying values
	printf("\n");
	printf("ix = %d\n", pData->ix);
	printf("fy = %f\n", pData->fy);
	printf("dz = %lf\n", pData->dz);

	//freeing memory
	if(pData)
	{
		free(pData);
		pData = NULL;
		printf("\n");
		printf("Memory Freed: pData\n");
	}

	return(0);
}

void ChangeValues(struct Mydata *pParam_data)
{
	pParam_data->ix = 12;
	pParam_data->fy = 12.12f;
	pParam_data->dz = 122.122;
}
